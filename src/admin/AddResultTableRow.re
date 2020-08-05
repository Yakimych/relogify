open Utils;
open Queries;
open Mutations;
open Styles;
open ApolloHooks;

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

[@react.component]
let make = (~communityName: string, ~communitySettingsFragment) => {
  let communitySettings =
    AddResultTableRowFragment.use(communitySettingsFragment);

  let (addResultMutation, _, _) = useMutation(AddResultMutation.definition);

  let (maybePlayer1Name, setMaybePlayer1Name) = React.useState(_ => None);
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (maybePlayer2Name, setMaybePlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());
  let (isAddingResult, setIsAddingResult) = React.useState(_ => false);

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
      setIsAddingResult(_ => true);

      // TODO: Pass in a query to refetch instead? Consolidate with AddResult.re?
      addResultMutation(
        ~variables=
          AddResultMutation.makeVariables(
            ~communityName,
            ~player1Name,
            ~player2Name,
            ~date=date->withCurrentTime(Js.Date.make())->toJsonDate,
            ~player1Goals=goals1,
            ~player2Goals=goals2,
            ~extraTime,
            (),
          ),
        ~refetchQueries=
          _ =>
            [|
              // ApolloHooks.toQueryObj(
              //   AllResultsQuery.make(~communityName, ()),
              // ),
              ApolloHooks.toQueryObj(
                AllPlayersQuery.make(~communityName, ()),
              ),
            |],
        (),
      )
      |> Js.Promise.then_(_ =>
           setIsAddingResult(_ => false) |> Js.Promise.resolve
         )
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           setIsAddingResult(_ => false) |> Js.Promise.resolve;
         })
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
        communityName
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
        communityName
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
