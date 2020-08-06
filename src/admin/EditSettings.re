open Utils;
open Types;

// TODO: Style this component (including the alert)
[@bs.val] external alert: string => unit = "alert";

type editCommunitySettingsAction =
  | SetAllSettings(
      EditSettingsQuery_graphql.Types.response_community_settings_connection_edges_node,
    )
  | ToggleAllowDraws
  | ToggleIncludeExtraTime
  | SetScoreType(
      EditSettings_UpdateCommunitySettings_Mutation_graphql.enum_score_types_enum,
    )
  | SetMaxSelectablePoints(int);

let defaultCommunitySettings: EditSettingsQuery_graphql.Types.response_community_settings_connection_edges_node = {
  allow_draws: false,
  max_selectable_points: 9,
  score_type: `Goals,
  include_extra_time: true,
  use_dropdown_for_points: true,
};

let scoreTypeConversion_temp =
    (
      scoreType: EditSettings_UpdateCommunitySettings_Mutation_graphql.enum_score_types_enum,
    )
    : EditSettingsQuery_graphql.enum_score_types_enum =>
  switch (scoreType) {
  | `Goals => `Goals
  | `Points => `Points
  | _ => `Points
  };

let scoreTypeConversion_temp2 =
    (scoreType: EditSettingsQuery_graphql.enum_score_types_enum)
    : EditSettings_UpdateCommunitySettings_Mutation_graphql.enum_score_types_enum =>
  switch (scoreType) {
  | `Goals => `Goals
  | `Points => `Points
  | _ => `Points
  };

let scoreTypeConversion_temp3 =
    (scoreType: EditSettingsQuery_graphql.enum_score_types_enum)
    : EditSettings_CreateCommunitySettings_Mutation_graphql.enum_score_types_enum =>
  switch (scoreType) {
  | `Goals => `Goals
  | `Points => `Points
  | _ => `Points
  };

let reducer =
    (
      settings: EditSettingsQuery_graphql.Types.response_community_settings_connection_edges_node,
      action,
    )
    : EditSettingsQuery_graphql.Types.response_community_settings_connection_edges_node =>
  switch (action) {
  | SetAllSettings(allSettings) => allSettings
  | ToggleAllowDraws => {...settings, allow_draws: !settings.allow_draws}
  | ToggleIncludeExtraTime => {
      ...settings,
      include_extra_time: !settings.include_extra_time,
    }
  | SetScoreType(scoreType) => {
      ...settings,
      score_type: scoreTypeConversion_temp(scoreType),
    }
  | SetMaxSelectablePoints(maxSelectablePoints) => {
      ...settings,
      max_selectable_points: maxSelectablePoints,
    }
  };

let scoreTypeToString =
    (
      scoreType: EditSettings_UpdateCommunitySettings_Mutation_graphql.enum_score_types_enum,
    ) =>
  switch (scoreType) {
  | `Goals => "Goals"
  | `Points => "Points"
  | _ => "Unknown score type"
  };

let scoreTypeToString2 =
    (scoreType: EditSettingsQuery_graphql.enum_score_types_enum) =>
  switch (scoreType) {
  | `Goals => "Goals"
  | `Points => "Points"
  | _ => "Unknown score type"
  };

let scoreTypes = [|`Goals, `Points|]->Belt.Array.map(scoreTypeToString);
// let scoreTypes = [|"Goals", "Points"|];

module Query = [%relay.query
  {|
      query EditSettingsQuery($communityName: String!) {
        community_settings_connection(
          where: { community: { name: { _eq: $communityName } } }
        ) {
          edges {
            node {
              allow_draws
              max_selectable_points
              score_type
              use_dropdown_for_points
              include_extra_time
            }
          }
        }
      }
  |}
];

module UpdateCommunitySettingsMutation = [%relay.mutation
  {|
    mutation EditSettings_UpdateCommunitySettings_Mutation(
      $communityName: String!
      $allowDraws: Boolean
      $maxSelectablePoints: Int
      $scoreType: score_types_enum
      $includeExtraTime: Boolean
      $useDropDownForPoints: Boolean
    ) {
      update_community_settings(
        where: { community: { name: { _eq: $communityName } } }
        _set: {
          allow_draws: $allowDraws
          max_selectable_points: $maxSelectablePoints
          score_type: $scoreType
          include_extra_time: $includeExtraTime
          use_dropdown_for_points: $useDropDownForPoints
        }
      ) {
        affected_rows
      }
    }
  |}
];

module CreateCommunitySettingsMutation = [%relay.mutation
  {|
    mutation EditSettings_CreateCommunitySettings_Mutation(
      $input: community_settings_insert_input!
    ) {
      insert_community_settings_one(object: $input) {
        id
      }
    }
  |}
];

[@react.component]
let make = (~communityName: string) => {
  let queryData = Query.use(~variables={communityName: communityName}, ());
  let loadedCommunitySettings =
    queryData.community_settings_connection.edges->Belt.Array.get(0);

  let (updateSettings, _) = UpdateCommunitySettingsMutation.use();
  let (createSettings, _) = CreateCommunitySettingsMutation.use();

  let initialCommunitySettings =
    loadedCommunitySettings->Belt.Option.mapWithDefault(
      defaultCommunitySettings, s =>
      s.node
    );
  let (state, dispatch) =
    React.useReducer(reducer, initialCommunitySettings);

  let onSaveError = _ => {
    alert("Failed saving settings");
  };

  let onCreateCompleted = (_, maybeMutationErrors) => {
    switch (maybeMutationErrors) {
    | Some(_) => alert("Failed saving settings")
    | None => alert("Settings saved")
    };
  };

  let createCommunitySettings = () => {
    let createCommunitySettingsInput: EditSettings_CreateCommunitySettings_Mutation_graphql.Types.community_settings_insert_input = {
      community_id: None,
      community:
        Some({
          data: {
            name: Some(communityName),
            community_settings: None,
            description: None,
            id: None,
            players: None,
            results: None,
          },
          on_conflict:
            Some({
              constraint_: `communities_name_key,
              update_columns: [|`name|],
              where: None,
            }),
        }),
      allow_draws: Some(state.allow_draws),
      max_selectable_points: Some(state.max_selectable_points),
      score_type: Some(scoreTypeConversion_temp3(state.score_type)),
      include_extra_time: Some(state.include_extra_time),
      use_dropdown_for_points: Some(state.use_dropdown_for_points),
    };
    createSettings(
      ~onCompleted=onCreateCompleted,
      ~onError=onSaveError,
      ~variables={input: createCommunitySettingsInput},
      (),
    )
    |> ignore;
  };

  let onUpdateCompleted =
      (
        mutationResponse: UpdateCommunitySettingsMutation.Types.response,
        maybeMutationErrors,
      ) => {
    let maybeAffectedRows =
      mutationResponse.update_community_settings
      ->Belt.Option.map(r => r.affected_rows);
    switch (maybeMutationErrors, maybeAffectedRows) {
    | (Some(_), _)
    | (None, None) => alert("Failed saving settings")
    | (None, Some(0)) => createCommunitySettings()
    | (None, Some(affectedRows)) =>
      alert("Settings saved, affected rows " ++ string_of_int(affectedRows))
    };
  };

  let updateCommunitySettings = () => {
    updateSettings(
      ~onCompleted=onUpdateCompleted,
      ~onError=onSaveError,
      ~variables={
        communityName,
        allowDraws: Some(state.allow_draws),
        maxSelectablePoints: Some(state.max_selectable_points),
        scoreType: Some(scoreTypeConversion_temp2(state.score_type)),
        includeExtraTime: Some(state.include_extra_time),
        useDropDownForPoints: Some(state.use_dropdown_for_points),
      },
      (),
    )
    |> ignore;
  };

  <>
    <Header page={AdminSettingsPage(communityName)} />
    <MaterialUi.Container maxWidth=`Lg>
      <div className="admin-settings">
        <MaterialUi.FormControlLabel
          control={
            <MaterialUi.Checkbox
              color=`Default
              checked={state.allow_draws}
              onChange={_ => dispatch(ToggleAllowDraws)}
            />
          }
          label={text("Allow draws")}
        />
        <MaterialUi.FormControlLabel
          control={
            <MaterialUi.Checkbox
              color=`Default
              checked={state.include_extra_time}
              onChange={_ => dispatch(ToggleIncludeExtraTime)}
            />
          }
          label={text("Include Extra Time")}
        />
        <MaterialUi.TextField
          type_="number"
          variant=`Outlined
          style={ReactDOMRe.Style.make(
            ~width="200px",
            ~marginTop="10px",
            ~marginBottom="10px",
            (),
          )}
          value={`Int(state.max_selectable_points)}
          label={text("Max selectable points")}
          onChange={e => {
            let selectablePointsString = ReactEvent.Form.target(e)##value;
            dispatch(
              SetMaxSelectablePoints(int_of_string(selectablePointsString)),
            );
          }}
        />
        {text("Score type: ")}
        // TODO: Style this without inline styles
        <MaterialUi.NativeSelect
          value={state.score_type |> scoreTypeToString2}
          style={ReactDOMRe.Style.make(
            ~width="200px",
            ~marginBottom="10px",
            (),
          )}
          onChange={e => {
            let scoreTypeString = ReactEvent.Form.target(e)##value;
            dispatch(SetScoreType(scoreTypeString |> toScoreType));
          }}
          input={
            <MaterialUi.OutlinedInput
              labelWidth={`Int(0)}
              style={ReactDOMRe.Style.make(~width="150px", ())}
            />
          }>
          {scoreTypes->Belt.Array.map(scoreType =>
             <option value=scoreType key=scoreType>
               {text(scoreType)}
             </option>
           )
           |> React.array}
        </MaterialUi.NativeSelect>
        <MaterialUi.Button
          variant=`Contained
          color=`Primary
          style={ReactDOMRe.Style.make(~width="100px", ())}
          onClick={_ => updateCommunitySettings()}>
          {text("Save")}
        </MaterialUi.Button>
      </div>
    </MaterialUi.Container>
  </>;
};
