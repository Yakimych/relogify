open Utils;
open LeaderboardUtils;
open PlayerStatsUtils;
open Streaks;
open Types;
open Queries;
open EloUtils;

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let playerResultsQuery =
    PlayerResultsQueryConfig.make(~communityName, ~playerName, ());

  let (playerResultsQuery, _) =
    PlayerResultsQuery.use(~variables=playerResultsQuery##variables, ());

  <>
    <Header page={PlayerHome(communityName, playerName)} />
    {switch (playerResultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let results = data##results |> toRecord;
       let playerStats: playerStats = getPlayerStats(playerName, results);

       let streaks = getAllStreaks(playerName, results);
       let state = results |> attachRatings;

       <>
         <Box textAlign="center">
           <Typography variant="h4"> {text(playerName)} </Typography>
           <Typography>
             {text("Total wins: " ++ string_of_int(playerStats.matchesWon))}
           </Typography>
           <Typography>
             {text(
                "Total losses: " ++ string_of_int(playerStats.matchesLost),
              )}
           </Typography>
           <Typography>
             {text(
                "Win/Loss ratio: "
                ++ formatPercentage(playerStats |> matchesWonPerPlayed),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals scored: "
                ++ string_of_int(playerStats.goalsScored),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals conceded: "
                ++ string_of_int(playerStats.goalsConceded),
              )}
           </Typography>
           <Typography>
             {text(
                "All-time goal difference: "
                ++ (playerStats |> goalDiff |> formatDiff),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals scored per match: "
                ++ formatGoalsPerMatch(playerStats |> goalsScoredPerMatch),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals conceded per match: "
                ++ formatGoalsPerMatch(playerStats |> goalsConcededPerMatch),
              )}
           </Typography>
           {streaks
            ->getLongestStreak
            ->Belt.Option.mapWithDefault(React.null, streak =>
                <StreakView
                  streak
                  streakName="Longest past winning streak"
                  playerName
                />
              )}
           {streaks
            ->getCurrentStreak
            ->Belt.Option.mapWithDefault(React.null, streak =>
                <StreakView
                  streak
                  streakName="Ongoing winning streak"
                  playerName
                />
              )}
         </Box>
         <ResultsTable
           results={state.resultsWithRatings}
           mainPlayerName=playerName
           communityName
         />
       </>;
     }}
  </>;
};
