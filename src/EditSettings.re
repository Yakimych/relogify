open Utils;
open Queries;
open Mutations;
open Types;

// TODO: Style this component (including the alert)
[@bs.val] external alert: string => unit = "alert";

type editCommunitySettingsAction =
  | SetAllSettings(communitySettings)
  | ToggleAllowDraws
  | SetScoreType(scoreType)
  | SetMaxSelectablePoints(int);

let reducer = (settings, action): communitySettings =>
  switch (action) {
  | SetAllSettings(allSettings) => allSettings
  | ToggleAllowDraws => {...settings, allowDraws: !settings.allowDraws}
  | SetScoreType(scoreType) => {...settings, scoreType}
  | SetMaxSelectablePoints(maxSelectablePoints) => {
      ...settings,
      maxSelectablePoints,
    }
  };

let scoreTypes = [|`Goals, `Points|]->Belt.Array.map(scoreTypeToString);

[@react.component]
let make = (~communityName: string) => {
  let settingsQueryConfig =
    CommunitySettingsQueryConfig.make(~communityName, ());
  let (_, fullSettingsQuery) =
    CommunitySettingsQuery.use(~variables=settingsQueryConfig##variables, ());

  let (updateSettingsMutation, _, _) = UpdateCommunitySettingsMutation.use();

  let (state, dispatch) =
    React.useReducer(reducer, defaultCommunitySettings);

  let saveCommunitySettings = () => {
    // TODO: Create settings if they don't exist
    Js.Promise.(
      updateSettingsMutation(
        ~variables=
          UpdateCommunitySettingsMutationConfig.make(
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
      <Container maxWidth="lg">
        <div className="admin-settings">
          <FormControlLabel
            control={
              <Checkbox
                color="default"
                checked={state.allowDraws}
                onClick={_ => dispatch(ToggleAllowDraws)}
              />
            }
            label="Allow draws"
          />
          <TextField
            _type="number"
            variant="outlined"
            style={ReactDOMRe.Style.make(
              ~width="200px",
              ~marginTop="10px",
              ~marginBottom="10px",
              (),
            )}
            value={string_of_int(state.maxSelectablePoints)}
            label="Max selectable points"
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
          <NativeSelect
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
              <OutlinedInput
                labelWidth=0
                style={ReactDOMRe.Style.make(~width="150px", ())}
              />
            }>
            {scoreTypes->Belt.Array.map(scoreType =>
               <option value=scoreType key=scoreType>
                 {text(scoreType)}
               </option>
             )
             |> React.array}
          </NativeSelect>
          <Button
            variant="contained"
            color="primary"
            style={ReactDOMRe.Style.make(~width="100px", ())}
            onClick={_ => saveCommunitySettings()}>
            {text("Save")}
          </Button>
        </div>
      </Container>
    </>
  };
};
