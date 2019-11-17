open Styles;
open Utils;
open Types;

type editResultAction =
  | SetPlayer1Id(int)
  | SetPlayer2Id(int)
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
    <TableCell>
      <button onClick={_ => onSave(id, valuesUnderEdit)}>
        {text("Save")}
      </button>
      <button onClick=onCancel> {text("Cancel")} </button>
    </TableCell>
    <TableCell align="right">
      <ExistingPlayerPicker
        disabled
        communityName
        selectedPlayerId={valuesUnderEdit.player1Id}
        onChange={id => dispatch(SetPlayer1Id(id))}
      />
    </TableCell>
    <TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={valuesUnderEdit.player1Goals}
        onChange={g => dispatch(SetPlayer1Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell style=colonStyle> {text(":")} </TableCell>
    <TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={valuesUnderEdit.player2Goals}
        onChange={g => dispatch(SetPlayer2Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell>
      <ExistingPlayerPicker
        disabled
        communityName
        selectedPlayerId={valuesUnderEdit.player2Id}
        onChange={id => dispatch(SetPlayer2Id(id))}
      />
    </TableCell>
    <TableCell style=extraTimeStyle align="right">
      <Checkbox
        disabled
        color="default"
        checked={valuesUnderEdit.extraTime}
        onClick={_ => dispatch(ToggleExtraTime)}
      />
    </TableCell>
    <TableCell>
      <TextField
        disabled
        _type="date"
        value={formatDate(valuesUnderEdit.date)}
        onChange={e => {
          let dateString = ReactEvent.Form.target(e)##value;
          dispatch(SetDate(dateString));
        }}
      />
    </TableCell>
  </>;
};
