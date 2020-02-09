open Utils;
open Styles;
open Types;
open Mutations;
open UseCommunitySettings;
open ApolloHooks;

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
  | StartEditing(matchResult)
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
let make =
    (~results: list(matchResult), ~communityName: string, ~queryToRefetch) => {
  let settingsQuery = useCommunitySettings(communityName);

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
        ~variables=DeleteResultMutation.makeVariables(~resultId, ()),
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
          UpdateResultMutation.makeVariables(
            ~resultId,
            ~player1Id=editedValues.player1Id,
            ~player2Id=editedValues.player2Id,
            ~player1Goals=editedValues.player1Goals,
            ~player2Goals=editedValues.player2Goals,
            ~extraTime=editedValues.extraTime,
            ~date=editedValues.date->toJsonDate,
            (),
          ),
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
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
    <MaterialUi_Paper>
      <div className="title">
        <MaterialUi_Typography variant=`H6>
          {text("Results")}
        </MaterialUi_Typography>
      </div>
      <MaterialUi_Table size=`Small>
        <MaterialUi_TableHead>
          <MaterialUi_TableRow>
            <MaterialUi_TableCell> {text("Edit")} </MaterialUi_TableCell>
            <MaterialUi_TableCell align=`Right>
              {text("Player1")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell style=numberCellStyle>
              {text("G1")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell style=colonStyle />
            <MaterialUi_TableCell style=numberCellStyle>
              {text("G2")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell> {text("Player2")} </MaterialUi_TableCell>
            <MaterialUi_TableCell style=extraTimeStyle align=`Right>
              //TODO: title="Extra time">
               {text("E")} </MaterialUi_TableCell>
            <MaterialUi_TableCell style=dateStyle>
              {text("Date")}
            </MaterialUi_TableCell>
          </MaterialUi_TableRow>
        </MaterialUi_TableHead>
        <MaterialUi_TableBody>
          <AddResultTableRow communityName />
          {results
           ->Belt.List.map(result =>
               <MaterialUi_TableRow key={string_of_int(result.id)}>
                 {switch (state) {
                  | DeleteConfirmationPending(resultToDeleteId)
                      when result.id === resultToDeleteId =>
                    <>
                      <MaterialUi_TableCell>
                        <span> {text("Are you sure?")} </span>
                        <button onClick={_ => deleteResult()}>
                          {text("Yes")}
                        </button>
                        <button onClick={_ => dispatch(StopDeleting)}>
                          {text("No")}
                        </button>
                      </MaterialUi_TableCell>
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
                      <MaterialUi_TableCell>
                        <button
                          onClick={_ => dispatch(StartEditing(result))}>
                          {text("Edit")}
                        </button>
                        <button
                          onClick={_ => dispatch(DeleteRequested(result.id))}>
                          {text("Delete")}
                        </button>
                      </MaterialUi_TableCell>
                      <ResultTableRow result />
                    </>
                  | DeleteConfirmationPending(_)
                  | Editing(_) =>
                    <> <MaterialUi_TableCell /> <ResultTableRow result /> </>
                  | Deleting(id)
                  | Updating(id) =>
                    <>
                      <MaterialUi_TableCell>
                        {id === result.id
                           ? <MaterialUi_CircularProgress /> : React.null}
                      </MaterialUi_TableCell>
                      <ResultTableRow result />
                    </>
                  }}
               </MaterialUi_TableRow>
             )
           ->Array.of_list
           ->React.array}
        </MaterialUi_TableBody>
      </MaterialUi_Table>
    </MaterialUi_Paper>
  };
};
