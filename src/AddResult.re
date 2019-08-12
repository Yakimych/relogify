let fakePlayerNames = [|"FakePlayer1", "FakePlayer2"|];

// TODO: bs-date-fns or re-date?
let formatDate = (date: Js.Date.t) =>
  Js.Date.toISOString(date)->String.sub(0, 10);

[@bs.val] external alert: string => unit = "alert";

[@react.component]
let make = () => {
  let (player1Name, setPlayer1Name) = React.useState(_ => None);
  let (goals1, setGoals1) = React.useState(_ => 0);

  let (player2Name, setPlayer2Name) = React.useState(_ => None);
  let (goals2, setGoals2) = React.useState(_ => 0);

  let (extraTime, setExtraTime) = React.useState(_ => false);
  let toggleExtraTime = () => setExtraTime(oldExtraTime => !oldExtraTime);

  let (date, setDate) = React.useState(_ => Js.Date.make());
  let (isAddingResult, setIsAddingResult) = React.useState(_ => false);

  let addResult = () =>
    // TODO: Rewrite with pattern matching
    if (player1Name->Belt.Option.mapWithDefault(true, n =>
          n |> String.length === 0
        )
        || player2Name->Belt.Option.mapWithDefault(true, n =>
             n |> String.length === 0
           )) {
      alert("You must select both players!");
    } else if (goals1 === goals2) {
      alert("A game cannot end in a draw!");
    } else if (Js.Math.abs_int(goals1 - goals2) != 1 && extraTime) {
      alert(
        "Games with Extra Time cannot have more than one goal difference!",
      );
    } else if (player1Name === player2Name) {
      alert("You must select two DIFFERENT players!");
    } else {
      setIsAddingResult(_ => true);
      Js.log2("Adding result: ", player1Name);
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
          selectedPlayerName=player1Name
          onChange={v => setPlayer1Name(_ => Some(v))}
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
          selectedPlayerName=player2Name
          onChange={v => setPlayer2Name(_ => Some(v))}
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
