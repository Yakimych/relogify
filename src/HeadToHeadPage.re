type playerStats = {
  numberOfWins: int,
  numberOfLosses: int,
  goalsScored: int,
  goalsConceded: int,
};

let text = ReasonReact.string;

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
    <MaterialUiBox textAlign="center">
      <MaterialUiTypography variant="h5">
        {text("Head to Head")}
      </MaterialUiTypography>
      <MaterialUiTypography variant="h4">
        {text(player1Name ++ " vs " ++ player2Name)}
      </MaterialUiTypography>
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
    </MaterialUiBox>
  </>;
};
