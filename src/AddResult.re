open Utils;

let fakePlayerNames = [|"FakePlayer1", "FakePlayer2"|];

// TODO: Implement a pretty dialog instead
[@bs.val] external alert: string => unit = "alert";

[@react.component]
let make =
    (
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~communityName: string,
    ) => {
  let (maybePlayer1Name, setMaybePlayer1Name) = React.useState(_ => None);
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (maybePlayer2Name, setMaybePlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());
  let (isAddingResult, setIsAddingResult) = React.useState(_ => false);

  let addResult = () =>
    switch (maybePlayer1Name, maybePlayer2Name, goals1, goals2, extraTime) {
    | (None | Some(""), _, _, _, _)
    | (_, None | Some(""), _, _, _) => alert("You must select both players!")
    | (_, _, goals1, goals2, _) when goals1 === goals2 =>
      alert("A game cannot end in a draw!")
    | (_, _, goals1, goals2, extraTime)
        when Js.Math.abs_int(goals1 - goals2) != 1 && extraTime =>
      alert(
        "Games with Extra Time cannot have more than one goal difference!",
      )
    | (Some(player1Name), Some(player2Name), _, _, _)
        when player1Name === player2Name =>
      alert("You must select two DIFFERENT players!")
    | (Some(player1Name), Some(player2Name), goals1, goals2, extraTime) =>
      setIsAddingResult(_ => true);
      Js.logMany([|
        "Adding result: ",
        player1Name,
        string_of_int(goals1),
        string_of_int(goals2),
        player2Name,
        extraTime ? "ET" : "",
        formatDate(date),
      |]);
      setIsAddingResult(_ => false);
    };

  <>
    <Paper
      style={ReactDOMRe.Style.make(~width="550px", ~marginBottom="30px", ())}>
      <div style={ReactDOMRe.Style.make(~display="flex", ())}>
        <PlayerPicker
          disabled=isAddingResult
          placeholderText="Player1"
          playerNames=fakePlayerNames
          selectedPlayerName=maybePlayer1Name
          onChange={v => setMaybePlayer1Name(_ => Some(v))}
        />
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals1
          onChange={v => setGoals1(_ => v)}
        />
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals2
          onChange={v => setGoals2(_ => v)}
        />
        <PlayerPicker
          disabled=isAddingResult
          placeholderText="Player2"
          playerNames=fakePlayerNames
          selectedPlayerName=maybePlayer2Name
          onChange={v => setMaybePlayer2Name(_ => Some(v))}
        />
      </div>
    </Paper>
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
        onClick=addResult>
        {ReasonReact.string("Submit")}
      </Button>
      <FormControlLabel
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
      <TextField
        disabled=isAddingResult
        _type="date"
        value={formatDate(date)}
        onChange={e =>
          /* TODO: Validate before setting */
          setDate(_ => Js.Date.fromString(ReactEvent.Form.target(e)##value))}
      />
    </div>
  </>;
};
