open Utils;
open Queries;
open Mutations;
open UseCommunitySettings;

[@bs.val] external alert: string => unit = "alert";

[@react.component]
let make = (~communityName: string) => {
  // TODO: Is it possible to combine all those hooks into one and use both here and in AddResult?
  // TODO: Rewrite all useState into useReducer?
  let settingsQuery = useCommunitySettings(communityName);

  let (addResultMutation, _, _) = AddResultMutation.use();

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
          AddResultMutationConfig.make(
            ~communityName,
            ~player1Name,
            ~player2Name,
            ~date=date->withCurrentTime(Js.Date.make())->toJsonDate,
            ~player1Goals=goals1,
            ~player2Goals=goals2,
            ~extraTime,
            (),
          )##variables,
        ~refetchQueries=
          _ =>
            [|
              ReasonApolloHooks.Utils.toQueryObj(
                AllResultsQueryConfig.make(~communityName, ()),
              ),
              ReasonApolloHooks.Utils.toQueryObj(
                AllPlayersQueryConfig.make(~communityName, ()),
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

  switch (settingsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
    // TODO: Restyle this as a TableRow
    <Paper
      elevation=6
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
        <Button
          disabled=isAddingResult
          variant="contained"
          color="primary"
          onClick={_ => addResult(communitySettings.allowDraws)}>
          {text("Submit")}
        </Button>
        {communitySettings.includeExtraTime
           ? <FormControlLabel
               control={
                 <Checkbox
                   disabled=isAddingResult
                   color="default"
                   checked=extraTime
                   onClick=toggleExtraTime
                 />
               }
               label="Extra Time"
             />
           : React.null}
        <TextField
          disabled=isAddingResult
          _type="date"
          value={formatDate(date)}
          onChange={e => {
            let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
            if (DateFns.isValid(date)) {
              setDate(_ => date);
            };
          }}
        />
      </div>
    </Paper>
  };
};
