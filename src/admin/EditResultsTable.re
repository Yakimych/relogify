open Utils;
open Styles;
open Types;
open Mutations;
open ApolloHooks;

type editResultsTableState =
  | Idle
  | Editing(string, editableResultValues)
  | Updating(string)
  | DeleteConfirmationPending(string)
  | Deleting(string);

let apiRequestIsInProgress =
  fun
  | Updating(_)
  | Deleting(_) => true
  | _ => false;

type editResultsTableAction =
  | StartEditing(matchResult)
  | StopEditing
  | StartUpdating
  | DeleteRequested(string)
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
let make =
    (
      ~results: list(matchResult),
      ~playersFragment,
      ~communityName: string /*, ~queryToRefetch*/,
      ~communitySettingsFragment,
    ) => {
  let (updateResultMutation, _, _) =
    useMutation(UpdateResultMutation.definition);
  let (deleteResultMutation, _, _) =
    useMutation(DeleteResultMutation.definition);
  let (state, dispatch) = React.useReducer(editResultsTableReducer, Idle);

  let deleteResult = () => {
    switch (state) {
    | DeleteConfirmationPending(resultId) =>
      dispatch(StartDeleting);
      deleteResultMutation(
        ~variables=
          DeleteResultMutation.makeVariables(
            ~resultId=resultId |> int_of_string, // TODO: This will fail
            (),
          ),
        // ~refetchQueries=_ => [|queryToRefetch|],
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

  let updateResult = (resultId: string, editedValues: editableResultValues) => {
    switch (state) {
    | Editing(_) =>
      dispatch(StartUpdating);
      updateResultMutation(
        ~variables=
          UpdateResultMutation.makeVariables(
            ~resultId=resultId |> int_of_string,
            ~player1Id=editedValues.player1Id |> int_of_string,
            ~player2Id=editedValues.player2Id |> int_of_string,
            ~player1Goals=editedValues.player1Goals,
            ~player2Goals=editedValues.player2Goals,
            ~extraTime=editedValues.extraTime,
            ~date=editedValues.date->toJsonDate,
            (),
          ),
        // ~refetchQueries=_ => [|queryToRefetch|],
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

  <MaterialUi.Paper>
    <div className="title">
      <MaterialUi.Typography variant=`H6>
        {text("Results")}
      </MaterialUi.Typography>
    </div>
    <MaterialUi.Table size=`Small>
      <MaterialUi.TableHead>
        <MaterialUi.TableRow>
          <MaterialUi.TableCell> {text("Edit")} </MaterialUi.TableCell>
          <MaterialUi.TableCell align=`Right>
            {text("Player1")}
          </MaterialUi.TableCell>
          <MaterialUi.TableCell style=numberCellStyle>
            {text("G1")}
          </MaterialUi.TableCell>
          <MaterialUi.TableCell style=colonStyle />
          <MaterialUi.TableCell style=numberCellStyle>
            {text("G2")}
          </MaterialUi.TableCell>
          <MaterialUi.TableCell> {text("Player2")} </MaterialUi.TableCell>
          <MaterialUi.TableCell style=extraTimeStyle align=`Right>
            <MaterialUi.Tooltip title={text("Extra time")} placement=`Top>
              <div> {text("E")} </div>
            </MaterialUi.Tooltip>
          </MaterialUi.TableCell>
          <MaterialUi.TableCell style=dateStyle>
            {text("Date")}
          </MaterialUi.TableCell>
        </MaterialUi.TableRow>
      </MaterialUi.TableHead>
      <MaterialUi.TableBody>
        <AddResultTableRow
          communityName
          communitySettingsFragment
          playerPickerFragment=playersFragment
        />
        {results
         ->Belt.List.map(result =>
             <MaterialUi.TableRow key={result.id}>
               {switch (state) {
                | DeleteConfirmationPending(resultToDeleteId)
                    when result.id === resultToDeleteId =>
                  <>
                    <MaterialUi.TableCell>
                      <span> {text("Are you sure?")} </span>
                      <button onClick={_ => deleteResult()}>
                        {text("Yes")}
                      </button>
                      <button onClick={_ => dispatch(StopDeleting)}>
                        {text("No")}
                      </button>
                    </MaterialUi.TableCell>
                    <ResultTableRow result />
                  </>
                | Editing(id, editedValues) when result.id === id =>
                  <EditResultTableRow
                    existingPlayerPickerFragment=playersFragment
                    communitySettingsFragment
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
                    <MaterialUi.TableCell>
                      <button onClick={_ => dispatch(StartEditing(result))}>
                        {text("Edit")}
                      </button>
                      <button
                        onClick={_ => dispatch(DeleteRequested(result.id))}>
                        {text("Delete")}
                      </button>
                    </MaterialUi.TableCell>
                    <ResultTableRow result />
                  </>
                | DeleteConfirmationPending(_)
                | Editing(_) =>
                  <> <MaterialUi.TableCell /> <ResultTableRow result /> </>
                | Deleting(id)
                | Updating(id) =>
                  <>
                    <MaterialUi.TableCell>
                      {id === result.id
                         ? <MaterialUi.CircularProgress /> : React.null}
                    </MaterialUi.TableCell>
                    <ResultTableRow result />
                  </>
                }}
             </MaterialUi.TableRow>
           )
         ->Array.of_list
         ->React.array}
      </MaterialUi.TableBody>
    </MaterialUi.Table>
  </MaterialUi.Paper>;
};
