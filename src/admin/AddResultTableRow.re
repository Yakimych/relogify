open StoreUpdater;
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

let nameOfPlayersConnectionToUpdate = "EditResults_query_players_connection";
let nameOfResultsConnectionToUpdate = "EditResults_query_results_connection";
let mutationFieldName = "insert_results_one";
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

  let (mutate, isAddingResult) = AddMutation.use();

  let (maybePlayer1Name, setMaybePlayer1Name) = React.useState(_ => None);
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (maybePlayer2Name, setMaybePlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());

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
      let communityInput: AddResultTableRowMutation_graphql.Types.communities_obj_rel_insert_input =
        AddResultTableRowMutation_graphql.Utils.(
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

      let playersOnConflictInput: AddResultTableRowMutation_graphql.Types.players_on_conflict = {
        constraint_: `players_name_communityId_key,
        update_columns: [|`name|],
        where: None,
      };

      mutate(
        ~updater=
          (store: ReasonRelay.RecordSourceSelectorProxy.t, _response) => {
            updateResultList(
              store,
              mutationFieldName,
              nameOfResultsConnectionToUpdate,
            );
            updatePlayerList(
              store,
              mutationFieldName,
              nameOfPlayersConnectionToUpdate,
              ["player1"],
            );
            updatePlayerList(
              store,
              mutationFieldName,
              nameOfPlayersConnectionToUpdate,
              ["player2"],
            );
          },
        ~variables=
          AddResultTableRowMutation_graphql.Utils.(
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
