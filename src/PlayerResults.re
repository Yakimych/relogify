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
     | (_, Loading) => <MaterialUi.CircularProgress />
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
         <MaterialUi.Box textAlign="center">
           <MaterialUi.Typography variant=`H4>
             {text(playerName)}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text("Total wins: " ++ string_of_int(playerStats.matchesWon))}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                "Total losses: " ++ string_of_int(playerStats.matchesLost),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                "Win/Loss ratio: "
                ++ formatPercentage(playerStats |> matchesWonPerPlayed),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                texts.totalPointsWon
                ++ ": "
                ++ string_of_int(playerStats.goalsScored),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                texts.totalPointsLost
                ++ ": "
                ++ string_of_int(playerStats.goalsConceded),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                texts.allTimePointDiff
                ++ ": "
                ++ (playerStats |> goalDiff |> formatDiff),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                texts.totalPointsWonPerMatch
                ++ ": "
                ++ formatGoalsPerMatch(playerStats |> goalsScoredPerMatch),
              )}
           </MaterialUi.Typography>
           <MaterialUi.Typography>
             {text(
                texts.totalPointsLostPerMatch
                ++ ": "
                ++ formatGoalsPerMatch(playerStats |> goalsConcededPerMatch),
              )}
           </MaterialUi.Typography>
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
         </MaterialUi.Box>
         <ResultsTable
           results={state.resultsWithRatings}
           mainPlayerName=playerName
           communityName
         />
       </>;
     }}
  </>;
};
