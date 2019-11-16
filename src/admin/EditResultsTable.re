open Styles;
open Utils;
open Types;
open Mutations;
open UseCommunitySettings;

// TODO: Move into the EditResultTableRow component?
let toEditableResult = (result: result): EditResultTableRow.editableResult => {
  id: result.id,
  player1Id: result.player1.id,
  player2Id: result.player2.id,
  player1Goals: result.player1goals,
  player2Goals: result.player2goals,
  extraTime: result.extratime,
  date: result.date,
};

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

type editResultsTableState =
  | Idle
  | Editing(EditResultTableRow.editableResult)
  | Updating(int)
  | DeleteConfirmationPending(int)
  | Deleting(int);

let apiRequestIsInProgress =
  fun
  | Updating(_)
  | Deleting(_) => true
  | _ => false;

// let mapState =
//     (
//       fn:
//         EditResultTableRow.editableResult => EditResultTableRow.editableResult,
//       state: editResultsTableState,
//     ) =>
//   switch (state) {
//   | Editing(result) => Editing(result->fn)
//   | _ => state
//   };

type editResultsTableAction =
  | StartEditing(result)
  | StopEditing
  | StartUpdating
  | DeleteRequested(int)
  | StopDeleting
  | StartDeleting;

let editResultsTableReducer =
    (state: editResultsTableState, action: editResultsTableAction) =>
  switch (action) {
  | StartEditing(result) => Editing(result->toEditableResult)
  | StartUpdating =>
    switch (state) {
    | Editing(result) => Updating(result.id)
    | _ => state
    }
  | StopEditing
  | StopDeleting => Idle
  | DeleteRequested(resultId) => DeleteConfirmationPending(resultId)
  | StartDeleting =>
    switch (state) {
    | DeleteConfirmationPending(resultId) => Deleting(resultId)
    | _ => state
    }
  };

[@react.component]
let make = (~results: list(result), ~communityName: string, ~queryToRefetch) => {
  let settingsQuery = useCommunitySettings(communityName);

  let (updateResultMutation, _, _) = UpdateResultMutation.use();
  let (deleteResultMutation, _, _) = DeleteResultMutation.use();
  let (state, dispatch) = React.useReducer(editResultsTableReducer, Idle);

  let deleteResult = () => {
    switch (state) {
    | DeleteConfirmationPending(resultId) =>
      dispatch(StartDeleting);
      deleteResultMutation(
        ~variables=DeleteResultMutationConfig.make(~resultId, ())##variables,
        ~refetchQueries=_ => [|queryToRefetch|],
        // TODO: Update local apollo cache manually instead of refetchQueries
        (),
      )
      |> Js.Promise.then_(_ => dispatch(StopEditing) |> Js.Promise.resolve)
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           dispatch(StopDeleting) |> Js.Promise.resolve;
         })
      |> ignore;
    | Editing(_)
    | Updating(_)
    | Idle
    | Deleting(_) => ()
    };
  };

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
        // TODO: Update local apollo cache manually instead of refetchQueries
        (),
      )
      |> Js.Promise.then_(_ => dispatch(StopEditing) |> Js.Promise.resolve)
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           dispatch(StopEditing) |> Js.Promise.resolve;
         })
      |> ignore;
    | Updating(_)
    | Idle
    | DeleteConfirmationPending(_)
    | Deleting(_) => ()
    };
  };

  switch (settingsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
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
                    | Idle =>
                      <>
                        <button
                          onClick={_ => dispatch(StartEditing(result))}>
                          {text("Edit")}
                        </button>
                        <button
                          onClick={_ => dispatch(DeleteRequested(result.id))}>
                          {text("Delete")}
                        </button>
                      </>
                    | DeleteConfirmationPending(resultToDeleteId) =>
                      result.id === resultToDeleteId
                        ? <>
                            <span> {text("Are you sure?")} </span>
                            <button onClick={_ => deleteResult()}>
                              {text("Yes")}
                            </button>
                            <button onClick={_ => dispatch(StopDeleting)}>
                              {text("No")}
                            </button>
                          </>
                        : React.null
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
                    | Deleting(id)
                    | Updating(id) =>
                      id === result.id ? <CircularProgress /> : React.null
                    }}
                 </TableCell>
                 {switch (state) {
                  | Editing(r) when r.id == result.id =>
                    <EditResultTableRow
                      communityName
                      communitySettings
                      editableResult=r
                      disabled={apiRequestIsInProgress(state)}
                    />
                  | Editing(_)
                  | Updating(_)
                  | Deleting(_)
                  | DeleteConfirmationPending(_)
                  | Idle =>
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
                      <TableCell>
                        {text(formatDate(result.date))}
                      </TableCell>
                    </>
                  }}
               </TableRow>
             )
           ->Array.of_list
           ->React.array}
        </TableBody>
      </Table>
    </Paper>
  };
};
