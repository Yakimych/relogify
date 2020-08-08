open Utils;
open Styles;

[@bs.val] external alert: string => unit = "alert";

module AddResultTableRowFragment = [%relay.fragment
  {|
    fragment AddResultTableRowFragment_CommunitySettings on community_settings {
      score_type
      max_selectable_points
      allow_draws
    }
  |}
];

module AddMutation = [%relay.mutation
  {|
    mutation AddResultTableRowMutation($input: results_insert_input!) {
      insert_results_one(object: $input) {
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
  |}
];

[@react.component]
let make =
    (
      ~communityName: string,
      ~communitySettingsFragment,
      ~playerPickerFragment,
    ) => {
  let communitySettings =
    AddResultTableRowFragment.use(communitySettingsFragment);

  let (addResult, isAddingResult) = AddMutation.use();

  let (maybePlayer1Name, setMaybePlayer1Name) = React.useState(_ => None);
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (maybePlayer2Name, setMaybePlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());

  let addResultUpdater =
      (
        store: ReasonRelay.RecordSourceSelectorProxy.t,
        _response: AddMutation.Types.response,
      ) => {
    // TODO: Add returned players to the store too
    ReasonRelayUtils.(
      switch (
        resolveNestedRecord(
          ~rootRecord=
            store->ReasonRelay.RecordSourceSelectorProxy.getRootField(
              ~fieldName="insert_results_one",
            ),
          ~path=[],
        )
      ) {
      | Some(node) =>
        createAndAddEdgeToConnections(
          ~store,
          ~node,
          ~connections=[
            {
              parentID: ReasonRelay.storeRootId,
              key: "EditResults_query_results_connection",
              filters: None,
            },
          ],
          ~edgeName="resultsEdge",
          ~insertAt=End,
        )
      | None => ()
      }
    );
  };

  let addResult = allowDraws => {
    let validationResult =
      ResultValidation.canAddResult(
        allowDraws,
        maybePlayer1Name,
        maybePlayer2Name,
        goals1,
        goals2,
        extraTime,
      );

    switch (validationResult) {
    | Error(message) => alert(message)
    | Ok((player1Name, player2Name)) =>
      let communityInput: AddResultTableRowMutation_graphql.Types.communities_obj_rel_insert_input = {
        data: {
          community_settings: None,
          description: None,
          id: None,
          name: Some(communityName),
          players: None,
          results: None,
        },
        on_conflict:
          Some({
            constraint_: `communities_name_key,
            update_columns: [|`name|],
            where: None,
          }),
      };

      let playersOnConflictInput: AddResultTableRowMutation_graphql.Types.players_on_conflict = {
        constraint_: `players_name_communityId_key,
        update_columns: [|`name|],
        where: None,
      };

      addResult(
        ~updater=addResultUpdater,
        ~variables={
          input: {
            community: Some(communityInput),
            player1:
              Some({
                data: {
                  community: Some(communityInput),
                  communityId: None,
                  id: None,
                  name: Some(player1Name),
                  resultsAsPlayer1: None,
                  resultsAsPlayer2: None,
                },
                on_conflict: Some(playersOnConflictInput),
              }),

            player2:
              Some({
                data: {
                  community: Some(communityInput),
                  communityId: None,
                  id: None,
                  name: Some(player2Name),
                  resultsAsPlayer1: None,
                  resultsAsPlayer2: None,
                },
                on_conflict: Some(playersOnConflictInput),
              }),

            comment: None,
            communityId: None,
            date: Some(date |> Js.Date.toISOString),
            extratime: Some(extraTime),
            id: None,
            player1Id: None,
            player1goals: Some(goals1),
            player2Id: None,
            player2goals: Some(goals2),
          },
        },
        (),
      )
      |> ignore;
    // ~refetchQueries=
    //   _ =>
    //     [|
    //       ApolloHooks.toQueryObj(
    //         AllPlayersQuery.make(~communityName, ()),
    //       ),
    //     |],
    //   (),
    // )
    // |> Js.Promise.then_(_ =>
    //      setIsAddingResult(_ => false) |> Js.Promise.resolve
    //    )
    // |> Js.Promise.catch(e => {
    //      Js.Console.error2("Error: ", e);
    //      setIsAddingResult(_ => false) |> Js.Promise.resolve;
    //    })
    };
  };

  <MaterialUi.TableRow>
    <MaterialUi.TableCell>
      <button
        disabled=isAddingResult
        onClick={_ => addResult(communitySettings.allow_draws)}>
        {text("Add")}
      </button>
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <PlayerPicker
        disabled=isAddingResult
        placeholderText="Player1"
        playerPickerFragment
        selectedPlayerName=maybePlayer1Name
        onChange={v => setMaybePlayer1Name(_ => Some(v))}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <GoalsPicker
        disabled=isAddingResult
        selectedGoals=goals1
        onChange={v => setGoals1(_ => v)}
        scoreType={communitySettings.score_type}
        maxSelectablePoints={communitySettings.max_selectable_points}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=colonStyle>
      {text(":")}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <GoalsPicker
        disabled=isAddingResult
        selectedGoals=goals2
        onChange={v => setGoals2(_ => v)}
        scoreType={communitySettings.score_type}
        maxSelectablePoints={communitySettings.max_selectable_points}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <PlayerPicker
        disabled=isAddingResult
        placeholderText="Player2"
        playerPickerFragment
        selectedPlayerName=maybePlayer2Name
        onChange={v => setMaybePlayer2Name(_ => Some(v))}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <MaterialUi.FormControlLabel
        control={
          <MaterialUi.Checkbox
            disabled=isAddingResult
            color=`Default
            checked=extraTime
            onChange={_ => toggleExtraTime()}
          />
        }
        label={text("Extra Time")}
      />
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <MaterialUi.TextField
        disabled=isAddingResult
        type_="date"
        value={`String(formatDate(date))}
        onChange={e => {
          let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
          if (DateFns.isValid(date)) {
            setDate(_ => date);
          };
        }}
      />
    </MaterialUi.TableCell>
  </MaterialUi.TableRow>;
};
