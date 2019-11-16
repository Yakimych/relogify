open Styles;
open Utils;
open Types;

type editableResult = {
  id: int,
  player1Id: int,
  player2Id: int,
  player1Goals: int,
  player2Goals: int,
  extraTime: bool,
  date: Js.Date.t,
};

type editResultAction =
  | SetPlayer1Id(int)
  | SetPlayer2Id(int)
  | SetPlayer1Goals(int)
  | SetPlayer2Goals(int)
  | ToggleExtraTime
  | SetDate(string);

let editResultReducer = (state: editableResult, action: editResultAction) =>
  switch (action) {
  | SetPlayer1Id(player1Id) => {...state, player1Id}
  | SetPlayer2Id(player2Id) => {...state, player2Id}
  | SetPlayer1Goals(player1Goals) => {...state, player1Goals}
  | SetPlayer2Goals(player2Goals) => {...state, player2Goals}
  | ToggleExtraTime => {...state, extraTime: !state.extraTime}
  | SetDate(dateString) =>
    let date = dateString->Js.Date.fromString;
    {...state, date: DateFns.isValid(date) ? date : state.date};
  };

[@react.component]
let make =
    (
      ~communityName,
      ~communitySettings: communitySettings,
      ~editableResult: editableResult,
      ~disabled,
    ) => {
  let (state, dispatch) =
    React.useReducer(editResultReducer, editableResult);

  <>
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
        selectedGoals={state.player1Goals}
        onChange={g => dispatch(SetPlayer1Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell style=colonStyle> {text(":")} </TableCell>
    <TableCell style=numberCellStyle>
      <GoalsPicker
        disabled
        selectedGoals={state.player2Goals}
        onChange={g => dispatch(SetPlayer2Goals(g))}
        maxSelectablePoints={communitySettings.maxSelectablePoints}
        scoreType={communitySettings.scoreType}
      />
    </TableCell>
    <TableCell>
      <ExistingPlayerPicker
        disabled
        communityName
        selectedPlayerId={state.player2Id}
        onChange={id => dispatch(SetPlayer2Id(id))}
      />
    </TableCell>
    <TableCell style=extraTimeStyle align="right">
      <Checkbox
        disabled
        color="default"
        checked={state.extraTime}
        onClick={_ => dispatch(ToggleExtraTime)}
      />
    </TableCell>
    <TableCell>
      <TextField
        disabled
        _type="date"
        value={formatDate(state.date)}
        onChange={e => {
          let dateString = ReactEvent.Form.target(e)##value;
          dispatch(SetDate(dateString));
        }}
      />
    </TableCell>
  </>;
};
