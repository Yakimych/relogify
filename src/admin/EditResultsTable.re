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
  | Loading => <MaterialUi.CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
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
          <AddResultTableRow communityName />
          {results
           ->Belt.List.map(result =>
               <MaterialUi.TableRow key={string_of_int(result.id)}>
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
                      <MaterialUi.TableCell>
                        <button
                          onClick={_ => dispatch(StartEditing(result))}>
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
    </MaterialUi.Paper>
  };
};
