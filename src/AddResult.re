open Utils;
open Queries;
open Mutations;
open StorageUtils;
open UseCommunitySettings;
open ApolloHooks;

// TODO: Implement a pretty dialog instead
[@bs.val] external alert: string => unit = "alert";

[@react.component]
let make = (~communityName: string, ~onResultAdded) => {
  let settingsQuery = useCommunitySettings(communityName);

  let (addResultMutation, _, _) = useMutation(AddResultMutation.definition);

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
  let (isAddingResult, setIsAddingResult) = React.useState(_ => false);

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
      setIsAddingResult(_ => true);
      updateUsedPlayers(player1Name, player2Name);

      // Will refetch query for current week after adding result
      let (startDate, endDate) = getCurrentWeek();
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
              ApolloHooks.toQueryObj(
                AllResultsQuery.make(
                  ~communityName,
                  ~dateFrom=startDate |> toJsonDate,
                  ~dateTo=endDate |> toJsonDate,
                  (),
                ),
              ),
              ApolloHooks.toQueryObj(
                AllPlayersQuery.make(~communityName, ()),
              ),
            |],
        (),
      )
      |> Js.Promise.then_(_ => {
           resetState();
           setIsAddingResult(_ => false);
           onResultAdded() |> Js.Promise.resolve;
         })
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           setIsAddingResult(_ => false) |> Js.Promise.resolve;
         })
      |> ignore;
    };
  };

  switch (settingsQuery) {
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
    <MaterialUi_Paper
      elevation={`Int(6)}
      style={ReactDOMRe.Style.make(~padding="25px 10px 10px 10px", ())}>
      <div
        style={ReactDOMRe.Style.make(
          ~display="flex",
          ~marginBottom="10px",
          (),
        )}>
        <PlayerPicker
          disabled=isAddingResult
          placeholderText="Player1"
          communityName
          selectedPlayerName=maybePlayer1Name
          onChange={v => setMaybePlayer1Name(_ => Some(v))}
        />
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals1
          onChange={v => setGoals1(_ => v)}
          scoreType={communitySettings.scoreType}
          maxSelectablePoints={communitySettings.maxSelectablePoints}
        />
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals2
          onChange={v => setGoals2(_ => v)}
          scoreType={communitySettings.scoreType}
          maxSelectablePoints={communitySettings.maxSelectablePoints}
        />
        <PlayerPicker
          disabled=isAddingResult
          placeholderText="Player2"
          communityName
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
        <MaterialUi_Button
          disabled=isAddingResult
          variant=`Contained
          color=`Primary
          onClick={_ => addResult(communitySettings.allowDraws)}>
          {text("Submit")}
        </MaterialUi_Button>
        {communitySettings.includeExtraTime
           ? <MaterialUi_FormControlLabel
               control={
                 <MaterialUi_Checkbox
                   disabled=isAddingResult
                   color=`Default
                   checked=extraTime
                   onChange={_ => toggleExtraTime()}
                 />
               }
               label={React.string("Extra Time")}
             />
           : React.null}
        <MaterialUi_TextField
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
    </MaterialUi_Paper>
  };
};
