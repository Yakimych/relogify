open StoreUpdater;
open Utils;
open StorageUtils;

// TODO: Implement a pretty dialog instead
[@bs.val] external alert: string => unit = "alert";

let nameOfPlayersConnectionToUpdate = "CommunityStartPage_query_players_connection";
let nameOfResultsConnectionToUpdate = "CommunityStartPage_query_results_connection";
let mutationFieldName = "insert_results_one";
module AddMutation = [%relay.mutation
  {|
    mutation AddResultMutation($input: results_insert_input!) {
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

module AddResultFragment = [%relay.fragment
  {|
    fragment AddResultFragment_CommunitySettings on community_settings
      @relay(plural: true) {
      include_extra_time
      score_type
      max_selectable_points
      allow_draws
    }
  |}
];

[@react.component]
let make =
    (
      ~communitySettingsFragments,
      ~playerPickerFragment,
      ~communityName: string,
      ~onResultAdded,
    ) => {
  let defaultCommunitySettings: AddResultFragment.Types.fragment_t = {
    include_extra_time: DefaultCommunitySettings.includeExtraTime,
    score_type: DefaultCommunitySettings.scoreType,
    max_selectable_points: DefaultCommunitySettings.maxSelectablePoints,
    allow_draws: DefaultCommunitySettings.allowDraws,
  };

  let communitySettingsFragment =
    AddResultFragment.use(communitySettingsFragments)
    |> Utils.headWithDefault(defaultCommunitySettings);

  let (mutate, isAddingResult) = AddMutation.use();

  let (getMostUsedPlayer, updateUsedPlayers) =
    useMostUsedPlayer(communityName);

  let (maybePlayer1Name, setMaybePlayer1Name) =
    React.useState(_ => getMostUsedPlayer());
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (maybePlayer2Name, setMaybePlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());

  let resetState = () => {
    setMaybePlayer1Name(_ => getMostUsedPlayer());
    setMaybePlayer2Name(_ => None);
    setGoals1(_ => 0);
    setGoals2(_ => 0);
    setExtraTime(_ => false);
    setDate(_ => Js.Date.make());
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
      updateUsedPlayers(player1Name, player2Name);

      let communityInput: AddMutation.Types.communities_obj_rel_insert_input =
        AddMutation.Operation.Utils.(
          make_communities_obj_rel_insert_input(
            ~data=make_communities_insert_input(~name=communityName, ()),
            ~on_conflict={
              constraint_: `communities_name_key,
              update_columns: [|`name|],
              where: None,
            },
            (),
          )
        );

      let playersOnConflictInput: AddMutation.Types.players_on_conflict = {
        constraint_: `players_name_communityId_key,
        update_columns: [|`name|],
        where: None,
      };

      mutate(
        ~updater=
          (store: ReasonRelay.RecordSourceSelectorProxy.t, response) => {
            switch (response.insert_results_one) {
            | Some(insertedResult) =>
              updateResultList(
                store,
                insertedResult.id,
                nameOfResultsConnectionToUpdate,
              );
              updatePlayerList(
                store,
                insertedResult.player1.id,
                nameOfPlayersConnectionToUpdate,
              );
              updatePlayerList(
                store,
                insertedResult.player2.id,
                nameOfPlayersConnectionToUpdate,
              );
            | None => ()
            }
          },
        ~onCompleted=
          (_, maybeMutationErrors) => {
            switch (maybeMutationErrors) {
            | Some(e) => Js.Console.error2("Error adding result", e)
            | None =>
              resetState();
              onResultAdded();
            }
          },
        ~variables=
          AddMutation.Operation.Utils.(
            AddMutation.makeVariables(
              ~input=
                make_results_insert_input(
                  ~community=communityInput,
                  ~player1=
                    make_players_obj_rel_insert_input(
                      ~data=
                        make_players_insert_input(
                          ~community=communityInput,
                          ~name=player1Name,
                          (),
                        ),
                      ~on_conflict=playersOnConflictInput,
                      (),
                    ),
                  ~player2=
                    make_players_obj_rel_insert_input(
                      ~data=
                        make_players_insert_input(
                          ~community=communityInput,
                          ~name=player2Name,
                          (),
                        ),
                      ~on_conflict=playersOnConflictInput,
                      (),
                    ),
                  ~date,
                  ~extratime=extraTime,
                  ~player1goals=goals1,
                  ~player2goals=goals2,
                  (),
                ),
            )
          ),
        (),
      )
      |> ignore;
    };
  };

  <MaterialUi.Paper
    elevation={`Int(6)}
    style={ReactDOMRe.Style.make(~padding="25px 10px 10px 10px", ())}>
    <div
      style={ReactDOMRe.Style.make(~display="flex", ~marginBottom="10px", ())}>
      <PlayerPicker
        disabled=isAddingResult
        placeholderText="Player1"
        playerPickerFragment
        selectedPlayerName=maybePlayer1Name
        onChange={v => setMaybePlayer1Name(_ => Some(v))}
      />
      <GoalsPicker
        disabled=isAddingResult
        selectedGoals=goals1
        onChange={v => setGoals1(_ => v)}
        scoreType={communitySettingsFragment.score_type}
        maxSelectablePoints={communitySettingsFragment.max_selectable_points}
      />
      <GoalsPicker
        disabled=isAddingResult
        selectedGoals=goals2
        onChange={v => setGoals2(_ => v)}
        scoreType={communitySettingsFragment.score_type}
        maxSelectablePoints={communitySettingsFragment.max_selectable_points}
      />
      <PlayerPicker
        disabled=isAddingResult
        placeholderText="Player2"
        playerPickerFragment
        selectedPlayerName=maybePlayer2Name
        onChange={v => setMaybePlayer2Name(_ => Some(v))}
      />
    </div>
    <div
      style={ReactDOMRe.Style.make(
        ~display="flex",
        ~justifyContent="space-between",
        (),
      )}>
      <MaterialUi.Button
        disabled=isAddingResult
        variant=`Contained
        color=`Primary
        onClick={_ => addResult(communitySettingsFragment.allow_draws)}>
        {text("Submit")}
      </MaterialUi.Button>
      {communitySettingsFragment.include_extra_time
         ? <MaterialUi.FormControlLabel
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
         : React.null}
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
    </div>
  </MaterialUi.Paper>;
};
