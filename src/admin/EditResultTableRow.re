open Styles;
open Utils;
open Types;

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

[@react.component]
let make =
    (
      ~communityName,
      ~communitySettings: communitySettings,
      ~id,
      ~initialValuesToEdit: editableResultValues,
      ~disabled,
      ~onSave,
      ~onCancel,
    ) => {
  let (valuesUnderEdit, dispatch) =
    React.useReducer(editResultReducer, initialValuesToEdit);

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
        communityName
        selectedPlayerId={valuesUnderEdit.player1Id}
        onChange={id => dispatch(SetPlayer1Id(id))}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={valuesUnderEdit.player1Goals}
        onChange={g => dispatch(SetPlayer1Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
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
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <ExistingPlayerPicker
        disabled
        communityName
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
