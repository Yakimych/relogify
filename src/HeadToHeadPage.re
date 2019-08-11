type playerStats = {
  numberOfWins: int,
  numberOfLosses: int,
  goalsScored: int,
  goalsConceded: int,
};

let text = ReasonReact.string;

let fakePlayer1: ResultsTable.player = {name: "FakePlayer1"};

let fakePlayer2: ResultsTable.player = {name: "FakePlayer2"};

let fakeResult: ResultsTable.result = {
  id: 1,
  player1: fakePlayer1,
  player2: fakePlayer2,
  player1goals: 5,
  player2goals: 0,
  date: "2019-02-03",
  extratime: false,
};

let fakeResults: array(ResultsTable.result) = [|fakeResult|];

[@react.component]
let make = (~communityName, ~player1Name, ~player2Name) => {
  let stats = {
    numberOfWins: 10,
    numberOfLosses: 2,
    goalsScored: 55,
    goalsConceded: 12,
  };

  <>
    <div>
      <Link url={"/" ++ communityName}> {text("Start page")} </Link>
    </div>
    <Box textAlign="center">
      <Typography variant="h5"> {text("Head to Head")} </Typography>
      <Typography variant="h4">
        {text(player1Name ++ " vs " ++ player2Name)}
      </Typography>
      <div>
        <span className="stats-player-goals">
          {text("(" ++ string_of_int(stats.goalsScored) ++ ")")}
        </span>
        {text(" ")}
        <span className="stats-player-wins">
          {text(
             string_of_int(stats.numberOfWins)
             ++ "-"
             ++ string_of_int(stats.numberOfLosses),
           )}
        </span>
        {text(" ")}
        <span className="stats-player-goals">
          {text("(" ++ string_of_int(stats.goalsConceded) ++ ")")}
        </span>
      </div>
    </Box>
    <ResultsTable results=fakeResults communityName />
  </>;
};
