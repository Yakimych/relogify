open Utils;
open LeaderboardUtils;
open PlayerStatsUtils;
open Streaks;
open Types;

module Query = [%relay.query
  {|
    query PlayerResultsQuery($communityName: String!, $playerName: String!) {
      results_connection(
        where: {
          _and: [
            { community: { name: { _eq: $communityName } } }
            {
              _or: [
                { player1: { name: { _eq: $playerName } } }
                { player2: { name: { _eq: $playerName } } }
              ]
            }
          ]
        }
        order_by: { date: desc }
      ) {
        ...ResultsTable_Results
        edges {
          node {
            id
            player1 {
              id
              name
            }
            player1goals
            player2 {
              id
              name
            }
            player2goals
            date
            extratime
          }
        }
      }
    
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...ExtraTimeColumn_IncludeExtraTime
            ...ResultsTableHeader_CommunitySettings
            score_type
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let queryData = Query.use(~variables={communityName, playerName}, ());

  let resultsTableFragment = queryData.results_connection.fragmentRefs;

  let communitySettings =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0);
  let texts = Texts.getScoreTypeTexts(communitySettings.node.score_type);

  let communitySettingsFragment = communitySettings.node.fragmentRefs;

  let resultNodes =
    queryData.results_connection.edges
    ->Belt.Array.map(r => r.node)
    ->Belt.List.fromArray;
  let playerStats: playerStats = getPlayerStats(playerName, resultNodes);

  let streaks = getAllStreaks(playerName, resultNodes);
  // let state = results |> attachRatings;

  <>
    <Header page={PlayerHome(communityName, playerName)} />
    <MaterialUi.Box textAlign="center">
      <MaterialUi.Typography variant=`H4>
        {text(playerName)}
      </MaterialUi.Typography>
      <MaterialUi.Typography>
        {text("Total wins: " ++ string_of_int(playerStats.matchesWon))}
      </MaterialUi.Typography>
      <MaterialUi.Typography>
        {text("Total losses: " ++ string_of_int(playerStats.matchesLost))}
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
           <StreakView streak streakName="Ongoing winning streak" playerName />
         )}
    </MaterialUi.Box>
    <ResultsTable
      resultsTableFragment
      communitySettingsFragment
      mainPlayerName=playerName
      communityName
    />
  </>;
};
