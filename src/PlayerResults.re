open Utils;
open Types;

type playerStats = {
  numberOfWins: int,
  numberOfLosses: int,
  goalsScored: int,
  goalsConceded: int,
  streaks,
};

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let playerStats: playerStats = {
    numberOfWins: 3,
    numberOfLosses: 1,
    goalsScored: 22,
    goalsConceded: 11,
    streaks: {
      longestStreak:
        Some({
          numberOfMatches: 2,
          startedAt: Js.Date.make(),
          endedAt: None,
          endedBy: None,
        }),
      currentStreak: None,
    },
  };

  <div>
    <Box textAlign="center">
      <Typography variant="h5"> {text("Player results")} </Typography>
      <Typography variant="h4"> {text(playerName)} </Typography>
      <Typography>
        {text("Total wins: " ++ string_of_int(playerStats.numberOfWins))}
      </Typography>
      <Typography>
        {text("Total losses: " ++ string_of_int(playerStats.numberOfLosses))}
      </Typography>
      <Typography>
        {text(
           "Total goals scored: " ++ string_of_int(playerStats.goalsScored),
         )}
      </Typography>
      <Typography>
        {text(
           "Total goals conceded: "
           ++ string_of_int(playerStats.goalsConceded),
         )}
      </Typography>
      {playerStats.streaks.longestStreak
       ->Belt.Option.mapWithDefault(ReasonReact.null, streak =>
           <StreakView streak streakName="Longest winning streak" />
         )}
      {playerStats.streaks.currentStreak
       ->Belt.Option.mapWithDefault(ReasonReact.null, streak =>
           <StreakView streak streakName="Ongoing winning streak" />
         )}
    </Box>
    <ResultsTable results=[||] mainPlayerName=playerName communityName />
    <Link url={"/" ++ communityName}> {text("Back to Start Page")} </Link>
  </div>;
};
