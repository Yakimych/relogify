open Styles;
open Utils;
open Types;
open Mutations;

type editableResult = {
  id: int,
  player1Id: int,
  player2Id: int,
  player1Goals: int,
  player2Goals: int,
  extraTime: bool,
  date: Js.Date.t,
};

let toEditableResult = (result: result) => {
  id: result.id,
  player1Id: result.player1.id,
  player2Id: result.player2.id,
  player1Goals: result.player1goals,
  player2Goals: result.player2goals,
  extraTime: result.extratime,
  date: result.date,
};

let colonStyle =
  ReactDOMRe.Style.make(
    ~width="5px",
    ~paddingLeft="0",
    ~paddingRight="0",
    (),
  );

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

let extraTimeStyle = ReactDOMRe.Style.make(~width="20px", ());

type editResultsTableState =
  | NotEditing
  | Editing(editableResult)
  | Updating(int);

let isUpdating =
  fun
  | Updating(_) => true
  | _ => false;

let mapState =
    (fn: editableResult => editableResult, state: editResultsTableState) =>
  switch (state) {
  | Editing(result) => Editing(result->fn)
  | _ => state
  };

type editResultsTableAction =
  | StartEditing(result)
  | StopEditing
  | StartUpdating
  | SetPlayer1Id(int)
  | SetPlayer2Id(int)
  | SetPlayer1Goals(int)
  | SetPlayer2Goals(int)
  | ToggleExtraTime
  | SetDate(string);

let editResultsTableReducer =
    (state: editResultsTableState, action: editResultsTableAction) =>
  switch (action) {
  | StartEditing(result) => Editing(result->toEditableResult)
  | StartUpdating =>
    switch (state) {
    | Editing(result) => Updating(result.id)
    | _ => state
    }
  | StopEditing => NotEditing
  | SetPlayer1Id(player1Id) => state |> mapState(r => {...r, player1Id})
  | SetPlayer2Id(player2Id) => state |> mapState(r => {...r, player2Id})
  | SetPlayer1Goals(player1Goals) =>
    state |> mapState(r => {...r, player1Goals})
  | SetPlayer2Goals(player2Goals) =>
    state |> mapState(r => {...r, player2Goals})
  | ToggleExtraTime => state |> mapState(r => {...r, extraTime: !r.extraTime})
  | SetDate(dateString) =>
    let date = dateString->Js.Date.fromString;
    state
    |> mapState(r => {...r, date: DateFns.isValid(date) ? date : r.date});
  };

[@react.component]
let make = (~results: list(result), ~communityName: string, ~queryToRefetch) => {
  let (updateResultMutation, _, _) = UpdateResultMutation.use();
  let (state, dispatch) =
    React.useReducer(editResultsTableReducer, NotEditing);

  let updateResult = () => {
    switch (state) {
    | Editing(resultToUpdate) =>
      dispatch(StartUpdating);
      updateResultMutation(
        ~variables=
          UpdateResultMutationConfig.make(
            ~resultId=resultToUpdate.id,
            ~player1Id=resultToUpdate.player1Id,
            ~player2Id=resultToUpdate.player2Id,
            ~player1Goals=resultToUpdate.player1Goals,
            ~player2Goals=resultToUpdate.player2Goals,
            ~extraTime=resultToUpdate.extraTime,
            ~date=resultToUpdate.date->toJsonDate,
            (),
          )##variables,
        ~refetchQueries=_ => [|queryToRefetch|],
        (),
      )
      |> Js.Promise.then_(_ => dispatch(StopEditing) |> Js.Promise.resolve)
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           dispatch(StopEditing) |> Js.Promise.resolve;
         })
      |> ignore;
    | Updating(_)
    | NotEditing => ()
    };
  };

  <Paper>
    <div className="title">
      <Typography variant="h6"> {text("Results")} </Typography>
    </div>
    <Table size="small">
      <TableHead>
        <TableRow>
          <TableCell> {text("Edit")} </TableCell>
          <TableCell align="right"> {text("Player1")} </TableCell>
          <TableCell style=numberCellStyle> {text("G1")} </TableCell>
          <TableCell style=colonStyle />
          <TableCell style=numberCellStyle> {text("G2")} </TableCell>
          <TableCell> {text("Player2")} </TableCell>
          <TableCell style=extraTimeStyle align="right" title="Extra time">
            {text("E")}
          </TableCell>
          <TableCell style=dateStyle> {text("Date")} </TableCell>
        </TableRow>
      </TableHead>
      <TableBody>
        {results
         ->Belt.List.map(result =>
             <TableRow key={string_of_int(result.id)}>
               <TableCell>
                 {switch (state) {
                  | NotEditing =>
                    <button onClick={_ => dispatch(StartEditing(result))}>
                      {text("Edit")}
                    </button>
                  | Editing(editedResult) =>
                    result.id === editedResult.id
                      ? <>
                          <button onClick={_ => updateResult()}>
                            {text("Save")}
                          </button>
                          <button onClick={_ => dispatch(StopEditing)}>
                            {text("Cancel")}
                          </button>
                        </>
                      : React.null
                  | Updating(updatingId) =>
                    updatingId === result.id
                      ? <CircularProgress /> : React.null
                  }}
               </TableCell>
               {switch (state) {
                | Editing(r) when r.id == result.id =>
                  <>
                    <TableCell align="right">
                      <ExistingPlayerPicker
                        disabled={isUpdating(state)}
                        communityName
                        selectedPlayerId={r.player1Id}
                        onChange={id => dispatch(SetPlayer1Id(id))}
                      />
                    </TableCell>
                    <TableCell style=numberCellStyle>
                      <GoalsPicker
                        disabled={state->isUpdating}
                        selectedGoals={r.player1Goals}
                        onChange={g => dispatch(SetPlayer1Goals(g))}
                      />
                    </TableCell>
                    <TableCell style=colonStyle> {text(":")} </TableCell>
                    <TableCell style=numberCellStyle>
                      <GoalsPicker
                        disabled={state->isUpdating}
                        selectedGoals={r.player2Goals}
                        onChange={g => dispatch(SetPlayer2Goals(g))}
                      />
                    </TableCell>
                    <TableCell>
                      <ExistingPlayerPicker
                        disabled={state->isUpdating}
                        communityName
                        selectedPlayerId={r.player2Id}
                        onChange={id => dispatch(SetPlayer2Id(id))}
                      />
                    </TableCell>
                    <TableCell style=extraTimeStyle align="right">
                      <Checkbox
                        disabled={state->isUpdating}
                        color="default"
                        checked={r.extraTime}
                        onClick={_ => dispatch(ToggleExtraTime)}
                      />
                    </TableCell>
                    <TableCell>
                      <TextField
                        disabled={state->isUpdating}
                        _type="date"
                        value={formatDate(r.date)}
                        onChange={e => {
                          let dateString = ReactEvent.Form.target(e)##value;
                          dispatch(SetDate(dateString));
                        }}
                      />
                    </TableCell>
                  </>
                | Editing(_)
                | Updating(_)
                | NotEditing =>
                  <>
                    <TableCell align="right">
                      <span> {text(result.player1.name)} </span>
                    </TableCell>
                    <TableCell style=numberCellStyle>
                      {text(string_of_int(result.player1goals))}
                    </TableCell>
                    <TableCell style=colonStyle> {text(":")} </TableCell>
                    <TableCell style=numberCellStyle>
                      {text(string_of_int(result.player2goals))}
                    </TableCell>
                    <TableCell>
                      <span> {text(result.player2.name)} </span>
                    </TableCell>
                    <TableCell style=extraTimeStyle align="right">
                      {text(result.extratime ? "X" : "")}
                    </TableCell>
                    <TableCell> {text(formatDate(result.date))} </TableCell>
                  </>
                }}
             </TableRow>
           )
         ->Array.of_list
         ->React.array}
      </TableBody>
    </Table>
  </Paper>;
};
