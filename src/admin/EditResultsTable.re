open Utils;
open Styles;
open Types;
open Mutations;
open UseCommunitySettings;

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

type editResultsTableState =
  | Idle
  | Editing(int, editableResultValues)
  | Updating(int)
  | DeleteConfirmationPending(int)
  | Deleting(int);

let apiRequestIsInProgress =
  fun
  | Updating(_)
  | Deleting(_) => true
  | _ => false;

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
  | StartEditing(result) =>
    Editing(result.id, result->toEditableResultValues)
  | StartUpdating =>
    switch (state) {
    | Editing(id, _) => Updating(id)
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
    | Deleting(_)
    | Idle => ()
    };
  };

  let updateResult = (resultId, editedValues: editableResultValues) => {
    switch (state) {
    | Editing(_) =>
      dispatch(StartUpdating);
      updateResultMutation(
        ~variables=
          UpdateResultMutationConfig.make(
            ~resultId,
            ~player1Id=editedValues.player1Id,
            ~player2Id=editedValues.player2Id,
            ~player1Goals=editedValues.player1Goals,
            ~player2Goals=editedValues.player2Goals,
            ~extraTime=editedValues.extraTime,
            ~date=editedValues.date->toJsonDate,
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
    | DeleteConfirmationPending(_)
    | Deleting(_)
    | Idle => ()
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
        <AdminAddResult communityName />
        <TableBody>
          {results
           ->Belt.List.map(result =>
               <TableRow key={string_of_int(result.id)}>
                 {switch (state) {
                  | DeleteConfirmationPending(resultToDeleteId)
                      when result.id === resultToDeleteId =>
                    <>
                      <TableCell>
                        <span> {text("Are you sure?")} </span>
                        <button onClick={_ => deleteResult()}>
                          {text("Yes")}
                        </button>
                        <button onClick={_ => dispatch(StopDeleting)}>
                          {text("No")}
                        </button>
                      </TableCell>
                      <ResultTableRow result />
                    </>
                  | Editing(id, editedValues) when result.id === id =>
                    <EditResultTableRow
                      communityName
                      communitySettings
                      initialValuesToEdit=editedValues
                      id
                      disabled={apiRequestIsInProgress(state)}
                      onSave={(id, editedResult) =>
                        updateResult(id, editedResult)
                      }
                      onCancel={_ => dispatch(StopEditing)}
                    />
                  | Idle =>
                    <>
                      <TableCell>
                        <button
                          onClick={_ => dispatch(StartEditing(result))}>
                          {text("Edit")}
                        </button>
                        <button
                          onClick={_ => dispatch(DeleteRequested(result.id))}>
                          {text("Delete")}
                        </button>
                      </TableCell>
                      <ResultTableRow result />
                    </>
                  | DeleteConfirmationPending(_)
                  | Editing(_) =>
                    <> <TableCell /> <ResultTableRow result /> </>
                  | Deleting(id)
                  | Updating(id) =>
                    <>
                      <TableCell>
                        {id === result.id ? <CircularProgress /> : React.null}
                      </TableCell>
                      <ResultTableRow result />
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
