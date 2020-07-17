open Utils;
open Queries;
open Mutations;
open Types;
open ApolloHooks;

// TODO: Style this component (including the alert)
[@bs.val] external alert: string => unit = "alert";

type editCommunitySettingsAction =
  | SetAllSettings(communitySettings)
  | ToggleAllowDraws
  | ToggleIncludeExtraTime
  | SetScoreType(scoreType)
  | SetMaxSelectablePoints(int);

let reducer = (settings, action): communitySettings =>
  switch (action) {
  | SetAllSettings(allSettings) => allSettings
  | ToggleAllowDraws => {...settings, allowDraws: !settings.allowDraws}
  | ToggleIncludeExtraTime => {
      ...settings,
      includeExtraTime: !settings.includeExtraTime,
    }
  | SetScoreType(scoreType) => {...settings, scoreType}
  | SetMaxSelectablePoints(maxSelectablePoints) => {
      ...settings,
      maxSelectablePoints,
    }
  };

let scoreTypes = [|`Goals, `Points|]->Belt.Array.map(scoreTypeToString);

[@react.component]
let make = (~communityName: string) => {
  let (_, fullSettingsQuery) =
    useQuery(
      ~variables=CommunitySettingsQuery.makeVariables(~communityName, ()),
      CommunitySettingsQuery.definition,
    );

  let (updateSettingsMutation, _, _) =
    useMutation(UpdateCommunitySettingsMutation.definition);
  let (createSettingsMutation, _, _) =
    useMutation(CreateCommunitySettingsMutation.definition);

  let (state, dispatch) =
    React.useReducer(reducer, defaultCommunitySettings);

  let saveCommunitySettings = () => {
    Js.Promise.(
      updateSettingsMutation(
        ~variables=
          UpdateCommunitySettingsMutation.make(
            ~communityName,
            ~allowDraws=state.allowDraws,
            ~maxSelectablePoints=state.maxSelectablePoints,
            ~scoreType=state.scoreType,
            ~includeExtraTime=state.includeExtraTime,
            ~useDropDownForPoints=state.useDropDownForPoints,
            (),
          )##variables,
        (),
      )
      |> then_(((executionResult, _)) => {
           switch (executionResult) {
           | ApolloHooks.Mutation.Errors(_) => resolve() // TODO: Handle errors
           | Data(d) =>
             // TODO: Simplify as soon as upsert is available on the backend
             let settingsUpdated =
               d##update_community_settings
               ->Belt.Option.mapWithDefault(false, s => s##affected_rows > 0);
             (
               if (!settingsUpdated) {
                 createSettingsMutation(
                   ~variables=
                     CreateCommunitySettingsMutation.make(
                       ~communityName,
                       ~allowDraws=state.allowDraws,
                       ~maxSelectablePoints=state.maxSelectablePoints,
                       ~scoreType=state.scoreType,
                       ~includeExtraTime=state.includeExtraTime,
                       ~useDropDownForPoints=state.useDropDownForPoints,
                       (),
                     )##variables,
                   (),
                 )
                 |> ignore;
               }
             )
             |> resolve;
           | _ => () |> resolve // TODO: Reject?
           }
         })
      |> then_(_ => alert("Settings saved") |> resolve)
      |> catch(e => {
           Js.Console.error2("Error when saving: ", e);
           alert("Error when saving") |> resolve;
         })
      |> ignore
    );
  };

  React.useEffect1(
    _ => {
      switch (fullSettingsQuery.data) {
      | Some(data) =>
        dispatch(SetAllSettings(data |> toCommunitySettings)) |> ignore
      | None => ()
      };
      None;
    },
    [|fullSettingsQuery.data|],
  );

  // TODO: Handle loading and error states
  switch (fullSettingsQuery.data) {
  | None => <div />
  | Some(_) =>
    <>
      <Header page={AdminSettingsPage(communityName)} />
      <MaterialUi_Container maxWidth=`Lg>
        <div className="admin-settings">
          <MaterialUi_FormControlLabel
            control={
              <MaterialUi_Checkbox
                color=`Default
                checked={state.allowDraws}
                onChange={_ => dispatch(ToggleAllowDraws)}
              />
            }
            label={text("Allow draws")}
          />
          <MaterialUi_FormControlLabel
            control={
              <MaterialUi_Checkbox
                color=`Default
                checked={state.includeExtraTime}
                onChange={_ => dispatch(ToggleIncludeExtraTime)}
              />
            }
            label={text("Include Extra Time")}
          />
          <MaterialUi_TextField
            type_="number"
            variant=`Outlined
            style={ReactDOMRe.Style.make(
              ~width="200px",
              ~marginTop="10px",
              ~marginBottom="10px",
              (),
            )}
            value={`Int(state.maxSelectablePoints)}
            label={text("Max selectable points")}
            onChange={e => {
              let selectablePointsString = ReactEvent.Form.target(e)##value;
              dispatch(
                SetMaxSelectablePoints(
                  int_of_string(selectablePointsString),
                ),
              );
            }}
          />
          {text("Score type: ")}
          // TODO: Style this without inline styles
          <MaterialUi_NativeSelect
            value={state.scoreType |> scoreTypeToString}
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
              <MaterialUi_OutlinedInput
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
          </MaterialUi_NativeSelect>
          <MaterialUi_Button
            variant=`Contained
            color=`Primary
            style={ReactDOMRe.Style.make(~width="100px", ())}
            onClick={_ => saveCommunitySettings()}>
            {text("Save")}
          </MaterialUi_Button>
        </div>
      </MaterialUi_Container>
    </>
  };
};
