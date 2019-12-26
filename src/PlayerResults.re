open Utils;
open LeaderboardUtils;
open PlayerStatsUtils;
open Streaks;
open Types;
open Queries;
open EloUtils;
open UseCommunitySettings;
open ApolloHooks;

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let (playerResultsQuery, _) =
    useQuery(
      ~variables=
        PlayerResultsQuery.makeVariables(~communityName, ~playerName, ()),
      PlayerResultsQuery.definition,
    );

  let settingsQuery = useCommunitySettings(communityName);

  <>
    <Header page={PlayerHome(communityName, playerName)} />
    {switch (playerResultsQuery, settingsQuery) {
     | (Loading, _)
     | (_, Loading) => <CircularProgress />
     | (NoData, _)
     | (_, NoData)
     | (Error(_), _)
     | (_, Error(_)) => <span> {text("Error")} </span>
     | (Data(resultsData), Data(communitySettings)) =>
       let results = resultsData##results |> toListOfResults;
       let texts = Texts.getScoreTypeTexts(communitySettings.scoreType);

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
                texts.totalPointsWon
                ++ ": "
                ++ string_of_int(playerStats.goalsScored),
              )}
           </Typography>
           <Typography>
             {text(
                texts.totalPointsLost
                ++ ": "
                ++ string_of_int(playerStats.goalsConceded),
              )}
           </Typography>
           <Typography>
             {text(
                texts.allTimePointDiff
                ++ ": "
                ++ (playerStats |> goalDiff |> formatDiff),
              )}
           </Typography>
           <Typography>
             {text(
                texts.totalPointsWonPerMatch
                ++ ": "
                ++ formatGoalsPerMatch(playerStats |> goalsScoredPerMatch),
              )}
           </Typography>
           <Typography>
             {text(
                texts.totalPointsLostPerMatch
                ++ ": "
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
