open Utils;
open Types;

// TODO: Style this component (including the alert)
[@bs.val] external alert: string => unit = "alert";

module EditSettingsFragment = [%relay.fragment
  {|
      fragment EditSettingsFragment_CommunitySettings on community_settings
        @relay(plural: true) {
        allow_draws
        max_selectable_points
        score_type
        use_dropdown_for_points
        include_extra_time
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

type editCommunitySettingsAction =
  | SetAllSettings(EditSettingsFragment.Types.fragment_t)
  | ToggleAllowDraws
  | ToggleIncludeExtraTime
  | SetScoreType(
      EditSettings_UpdateCommunitySettings_Mutation_graphql.enum_score_types_enum,
    )
  | SetMaxSelectablePoints(int);

let defaultCommunitySettings: EditSettingsFragment.Types.fragment_t = {
  allow_draws: false,
  max_selectable_points: 9,
  score_type: `Goals,
  include_extra_time: true,
  use_dropdown_for_points: true,
};

let convertScoreType = scoreType =>
  switch (scoreType) {
  | `Goals => `Goals
  | `Points => `Points
  | _ => `Points
  };

let reducer =
    (settings: EditSettingsFragment.Types.fragment_t, action)
    : EditSettingsFragment.Types.fragment_t =>
  switch (action) {
  | SetAllSettings(allSettings) => allSettings
  | ToggleAllowDraws => {...settings, allow_draws: !settings.allow_draws}
  | ToggleIncludeExtraTime => {
      ...settings,
      include_extra_time: !settings.include_extra_time,
    }
  | SetScoreType(scoreType) => {
      ...settings,
      score_type: convertScoreType(scoreType),
    }
  | SetMaxSelectablePoints(maxSelectablePoints) => {
      ...settings,
      max_selectable_points: maxSelectablePoints,
    }
  };

let scoreTypeToString = scoreType =>
  switch (scoreType) {
  | `Goals => "Goals"
  | `Points => "Points"
  | _ => "Unknown score type"
  };

let scoreTypes = [|`Goals, `Points|]->Belt.Array.map(scoreTypeToString);

[@react.component]
let make = (~communityName: string, ~editSettingsFragments) => {
  let initialCommunitySettings =
    EditSettingsFragment.use(editSettingsFragments)
    |> Utils.headWithDefault(defaultCommunitySettings);

  let (updateSettings, _) = UpdateCommunitySettingsMutation.use();
  let (createSettings, _) = CreateCommunitySettingsMutation.use();

  let (state, dispatch) =
    React.useReducer(reducer, initialCommunitySettings);

  let onSaveError = _ => alert("Failed saving settings");

  let onCreateCompleted = (_, maybeMutationErrors) => {
    switch (maybeMutationErrors) {
    | Some(_) => alert("Failed saving settings")
    | None => alert("Settings saved")
    };
  };

  let createCommunitySettings = () => {
    let mutationVariables =
      CreateCommunitySettingsMutation.makeVariables(
        ~input=
          CreateCommunitySettingsMutation.Operation.Utils.(
            make_community_settings_insert_input(
              ~community=
                make_communities_obj_rel_insert_input(
                  ~data=
                    make_communities_insert_input(~name=communityName, ()),
                  ~on_conflict=
                    make_communities_on_conflict(
                      ~constraint_=`communities_name_key,
                      ~update_columns=[|`name|],
                      (),
                    ),
                  (),
                ),
              ~allow_draws=state.allow_draws,
              ~max_selectable_points=state.max_selectable_points,
              ~score_type=convertScoreType(state.score_type),
              ~include_extra_time=state.include_extra_time,
              ~use_dropdown_for_points=state.use_dropdown_for_points,
              (),
            )
          ),
      );
    createSettings(
      ~onCompleted=onCreateCompleted,
      ~onError=onSaveError,
      ~variables=mutationVariables,
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
        scoreType: Some(convertScoreType(state.score_type)),
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
          value={state.score_type |> scoreTypeToString}
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
