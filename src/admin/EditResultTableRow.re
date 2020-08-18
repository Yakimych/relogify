open Types;
open Styles;
open Utils;

type editResultAction =
  | SetPlayer1Id(string)
  | SetPlayer2Id(string)
  | SetPlayer1Goals(int)
  | SetPlayer2Goals(int)
  | ToggleExtraTime
  | SetDate(string);

let editResultReducer =
    (valuesUnderEdit: editableResultValues, action: editResultAction) =>
  switch (action) {
  | SetPlayer1Id(player1Id) => {...valuesUnderEdit, player1Id}
  | SetPlayer2Id(player2Id) => {...valuesUnderEdit, player2Id}
  | SetPlayer1Goals(player1Goals) => {...valuesUnderEdit, player1Goals}
  | SetPlayer2Goals(player2Goals) => {...valuesUnderEdit, player2Goals}
  | ToggleExtraTime => {
      ...valuesUnderEdit,
      extraTime: !valuesUnderEdit.extraTime,
    }
  | SetDate(dateString) =>
    let date = dateString->Js.Date.fromString;
    {
      ...valuesUnderEdit,
      date: DateFns.isValid(date) ? date : valuesUnderEdit.date,
    };
  };

module CommunitySettingsFragment = [%relay.fragment
  {|
    fragment EditResultTableRowFragment_CommunitySettings on community_settings
      @relay(plural: true) {
      score_type
      max_selectable_points
    }
  |}
];

module SingleResultFragment = [%relay.fragment
  {|
    fragment EditResultTableRow_SingleResult on results {
      player1 {
        id
        name
      }
      player2 {
        id
        name
      }
      player2goals
      player1goals
      extratime
      date
      id
    }
  |}
];

[@react.component]
let make =
    (
      ~existingPlayerPickerFragment,
      ~communitySettingsFragments,
      ~id,
      ~resultFragment,
      ~disabled,
      ~onSave,
      ~onCancel,
    ) => {
  let resultFragment = SingleResultFragment.use(resultFragment);
  let initialValuesToEdit = resultFragment |> toEditableResultValues;
  let (valuesUnderEdit, dispatch) =
    React.useReducer(editResultReducer, initialValuesToEdit);

  let defaultCommunitySettings: CommunitySettingsFragment.Types.fragment_t = {
    score_type: DefaultCommunitySettings.scoreType,
    max_selectable_points: DefaultCommunitySettings.maxSelectablePoints,
  };

  let communitySettings =
    CommunitySettingsFragment.use(communitySettingsFragments)
    |> headWithDefault(defaultCommunitySettings);

  <>
    <MaterialUi.TableCell>
      <button onClick={_ => onSave(id, valuesUnderEdit)}>
        {text("Save")}
      </button>
      <button onClick=onCancel> {text("Cancel")} </button>
    </MaterialUi.TableCell>
    <MaterialUi.TableCell align=`Right>
      <ExistingPlayerPicker
        disabled
        existingPlayerPickerFragment
        selectedPlayerId={valuesUnderEdit.player1Id}
        onChange={id => dispatch(SetPlayer1Id(id))}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={valuesUnderEdit.player1Goals}
        onChange={g => dispatch(SetPlayer1Goals(g))}
        maxSelectablePoints={communitySettings.max_selectable_points}
        scoreType={communitySettings.score_type}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=colonStyle>
      {text(":")}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={valuesUnderEdit.player2Goals}
        onChange={g => dispatch(SetPlayer2Goals(g))}
        maxSelectablePoints={communitySettings.max_selectable_points}
        scoreType={communitySettings.score_type}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <ExistingPlayerPicker
        disabled
        existingPlayerPickerFragment
        selectedPlayerId={valuesUnderEdit.player2Id}
        onChange={id => dispatch(SetPlayer2Id(id))}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=extraTimeStyle align=`Right>
      <MaterialUi.Checkbox
        disabled
        color=`Default
        checked={valuesUnderEdit.extraTime}
        onChange={_ => dispatch(ToggleExtraTime)}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <MaterialUi.TextField
        disabled
        type_="date"
        value={`String(formatDate(valuesUnderEdit.date))}
        onChange={e => {
          let dateString = ReactEvent.Form.target(e)##value;
          dispatch(SetDate(dateString));
        }}
      />
    </MaterialUi.TableCell>
  </>;
};
