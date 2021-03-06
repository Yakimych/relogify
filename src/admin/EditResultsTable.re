open Utils;
open Styles;
open Types;

type editResultsTableState =
  | Idle
  | Editing(string)
  | Updating(string)
  | DeleteConfirmationPending(string)
  | Deleting(string);

let apiRequestIsInProgress =
  fun
  | Updating(_)
  | Deleting(_) => true
  | _ => false;

type editResultsTableAction =
  | StartEditing(string)
  | StopEditing
  | StartUpdating
  | DeleteRequested(string)
  | StopDeleting
  | StartDeleting;

let editResultsTableReducer =
    (state: editResultsTableState, action: editResultsTableAction) =>
  switch (action) {
  | StartEditing(resultId) => Editing(resultId)
  | StartUpdating =>
    switch (state) {
    | Editing(id) => Updating(id)
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

module UpdateMutation = [%relay.mutation
  {|
    mutation EditResultsTable_UpdateResult_Mutation(
      $resultId: Int!
      $player1Id: Int!
      $player2Id: Int!
      $player1Goals: Int!
      $player2Goals: Int!
      $extraTime: Boolean!
      $date: timestamptz!
    ) {
      update_results(
        where: { id: { _eq: $resultId } }
        _set: {
          player1Id: $player1Id
          player1goals: $player1Goals
          player2goals: $player2Goals
          player2Id: $player2Id
          extratime: $extraTime
          date: $date
        }
      ) {
        affected_rows
        returning {
          player1 {
            id
            name
          }
          player2 {
            id
            name
          }
          player2goals
          player1goals
          extratime
          date
          id
        }
      }
    }
  |}
];

module DeleteMutation = [%relay.mutation
  {|
    mutation EditResultsTable_DeleteResult_Mutation($resultId: Int!) {
      delete_results_by_pk(id: $resultId) {
        id
      }
    }
  |}
];

// TODO: Is there a way to only use Relay Ids with Hasura?
let toInternalId = [%raw
  {|
    function(relayId) {
      return Number(atob(relayId).split(" ").reverse()[0].replace("]", ""));
    }
  |}
];

module EditResultsTableFragment = [%relay.fragment
  {|
    fragment EditResultsTable_Results on resultsConnection {
      edges {
        node {
          ...ResultTableRow_SingleResult
          ...EditResultTableRow_SingleResult
          id
        }
      }
    }
  |}
];

[@react.component]
let make =
    (
      ~playersFragment,
      ~resultsFragment,
      ~communityName: string,
      ~communitySettingsFragments,
    ) => {
  let resultsFragment = EditResultsTableFragment.use(resultsFragment);

  let deleteUpdater =
      (
        store: ReasonRelay.RecordSourceSelectorProxy.t,
        response: DeleteMutation.Types.response,
      ) => {
    response.delete_results_by_pk
    ->Belt.Option.mapWithDefault(
        (),
        r => {
          let deletedItemId = r.id;

          switch (
            store->ReasonRelay.RecordSourceSelectorProxy.get(
              ~dataId=deletedItemId->ReasonRelay.makeDataId,
            )
          ) {
          | Some(node) =>
            ReasonRelayUtils.(
              removeNodeFromConnections(
                ~store,
                ~node,
                ~connections=[
                  {
                    parentID: ReasonRelay.storeRootId,
                    key: "EditResults_query_results_connection",
                    filters: None,
                  },
                ],
              )
            )
          | None => ()
          };
        },
      );
  };

  let (updateResultMutation, _) = UpdateMutation.use();
  let (deleteResultMutation, _) = DeleteMutation.use();

  let (state, dispatch) = React.useReducer(editResultsTableReducer, Idle);

  let deleteResult = () => {
    switch (state) {
    | DeleteConfirmationPending(resultId) =>
      dispatch(StartDeleting);
      deleteResultMutation(
        ~onCompleted=(_, _) => dispatch(StopDeleting),
        ~onError=maybeError => Js.log2("Error deleting result: ", maybeError),
        ~updater=deleteUpdater,
        ~variables={resultId: toInternalId(resultId)},
        (),
      )
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
        ~onCompleted=(_, _) => dispatch(StopEditing),
        ~onError=maybeError => Js.log2("Error updating result: ", maybeError),
        ~variables=
          UpdateMutation.Operation.Utils.makeVariables(
            ~resultId=resultId |> toInternalId,
            ~player1Id=editedValues.player1Id |> toInternalId,
            ~player2Id=editedValues.player2Id |> toInternalId,
            ~player1Goals=editedValues.player1Goals,
            ~player2Goals=editedValues.player2Goals,
            ~extraTime=editedValues.extraTime,
            ~date=editedValues.date,
          ),
        (),
      )
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
          communitySettingsFragments
          playerPickerFragment=playersFragment
        />
        {resultsFragment.edges
         ->Belt.Array.map(resultNode => resultNode.node)
         ->Belt.Array.map(result =>
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
                    <ResultTableRow resultFragment={result.fragmentRefs} />
                  </>
                | Editing(id) when result.id === id =>
                  <EditResultTableRow
                    existingPlayerPickerFragment=playersFragment
                    communitySettingsFragments
                    resultFragment={result.fragmentRefs}
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
                        onClick={_ => dispatch(StartEditing(result.id))}>
                        {text("Edit")}
                      </button>
                      <button
                        onClick={_ => dispatch(DeleteRequested(result.id))}>
                        {text("Delete")}
                      </button>
                    </MaterialUi.TableCell>
                    <ResultTableRow resultFragment={result.fragmentRefs} />
                  </>
                | DeleteConfirmationPending(_)
                | Editing(_) =>
                  <>
                    <MaterialUi.TableCell />
                    <ResultTableRow resultFragment={result.fragmentRefs} />
                  </>
                | Deleting(id)
                | Updating(id) =>
                  <>
                    <MaterialUi.TableCell>
                      {id === result.id
                         ? <MaterialUi.CircularProgress /> : React.null}
                    </MaterialUi.TableCell>
                    <ResultTableRow resultFragment={result.fragmentRefs} />
                  </>
                }}
             </MaterialUi.TableRow>
           )
         ->React.array}
      </MaterialUi.TableBody>
    </MaterialUi.Table>
  </MaterialUi.Paper>;
};
