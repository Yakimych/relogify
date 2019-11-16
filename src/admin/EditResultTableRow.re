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
    (resultUnderEdit: editableResult, action: editResultAction) =>
  switch (action) {
  | SetPlayer1Id(player1Id) => {...resultUnderEdit, player1Id}
  | SetPlayer2Id(player2Id) => {...resultUnderEdit, player2Id}
  | SetPlayer1Goals(player1Goals) => {...resultUnderEdit, player1Goals}
  | SetPlayer2Goals(player2Goals) => {...resultUnderEdit, player2Goals}
  | ToggleExtraTime => {
      ...resultUnderEdit,
      extraTime: !resultUnderEdit.extraTime,
    }
  | SetDate(dateString) =>
    let date = dateString->Js.Date.fromString;
    {
      ...resultUnderEdit,
      date: DateFns.isValid(date) ? date : resultUnderEdit.date,
    };
  };

[@react.component]
let make =
    (
      ~communityName,
      ~communitySettings: communitySettings,
      ~editableResult: editableResult,
      ~disabled,
      ~onSave,
      ~onCancel,
    ) => {
  let (resultUnderEdit, dispatch) =
    React.useReducer(editResultReducer, editableResult);

  <>
    <TableCell>
      <button onClick={_ => onSave(resultUnderEdit)}>
        {text("Save")}
      </button>
      <button onClick=onCancel> {text("Cancel")} </button>
    </TableCell>
    <TableCell align="right">
      <ExistingPlayerPicker
        disabled
        communityName
        selectedPlayerId={editableResult.player1Id}
        onChange={id => dispatch(SetPlayer1Id(id))}
      />
    </TableCell>
    <TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={resultUnderEdit.player1Goals}
        onChange={g => dispatch(SetPlayer1Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell style=colonStyle> {text(":")} </TableCell>
    <TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={resultUnderEdit.player2Goals}
        onChange={g => dispatch(SetPlayer2Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell>
      <ExistingPlayerPicker
        disabled
        communityName
        selectedPlayerId={resultUnderEdit.player2Id}
        onChange={id => dispatch(SetPlayer2Id(id))}
      />
    </TableCell>
    <TableCell style=extraTimeStyle align="right">
      <Checkbox
        disabled
        color="default"
        checked={resultUnderEdit.extraTime}
        onClick={_ => dispatch(ToggleExtraTime)}
      />
    </TableCell>
    <TableCell>
      <TextField
        disabled
        _type="date"
        value={formatDate(resultUnderEdit.date)}
        onChange={e => {
          let dateString = ReactEvent.Form.target(e)##value;
          dispatch(SetDate(dateString));
        }}
      />
    </TableCell>
  </>;
};
