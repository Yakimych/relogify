open Utils;
open EloUtils;
open LeaderboardUtils;

let topNumberOfRows = 5;
let byWinPercentage = (r1, r2) =>
  switch (r1 |> matchesWonPerPlayed, r2 |> matchesWonPerPlayed) {
  | (a, b) when a == b => sortCompareDesc(r1.matchesWon, r2.matchesWon)
  | (a, b) => sortCompareDesc(a, b)
  };

let byGoalsScored = (r1, r2) =>
  switch (r1 |> goalsScoredPerMatch, r2 |> goalsScoredPerMatch) {
  | (a, b) when a == b => sortCompareDesc(r1.goalsScored, r2.goalsScored)
  | (a, b) => sortCompareDesc(a, b)
  };

[@react.component]
let make = (~title, ~resultsWithMap: temp_resultsWithRatingMap, ~startDate) => {
  let relevantResultsWithRatings =
    resultsWithMap.resultsWithRatings
    ->Belt.List.keep(r => r.result.date >= startDate);

  let leaderboardRows =
    getLeaderboard(relevantResultsWithRatings->Belt.List.map(r => r.result));

  let sortedWinPercentageRows =
    leaderboardRows->Belt.List.sort(byWinPercentage);
  let topWinPercentageRows =
    sortedWinPercentageRows
    ->Belt.List.take(topNumberOfRows)
    ->Belt.Option.getWithDefault(sortedWinPercentageRows)
    ->Belt.List.map(row =>
        (row.playerName, row |> matchesWonPerPlayed |> formatPercentage)
      );

  let sortedGoalsScoredPerMatchRows =
    leaderboardRows->Belt.List.sort(byGoalsScored);
  let topGoalsScoredPerMatchRows =
    sortedGoalsScoredPerMatchRows
    ->Belt.List.take(topNumberOfRows)
    ->Belt.Option.getWithDefault(sortedGoalsScoredPerMatchRows)
    ->Belt.List.map(row =>
        (row.playerName, row |> goalsScoredPerMatch |> formatGoalsPerMatch)
      );

  <>
    <Paper>
      <div className="title">
        <Typography variant="h6"> {text(title)} </Typography>
      </div>
      <div className="top-stats-container">
        <SingleStatCard
          playersWithStat=topWinPercentageRows
          statName="Win Percentage"
          statHeader="Win %"
        />
        <SingleStatCard
          playersWithStat=topGoalsScoredPerMatchRows
          statName="Goals Scored per Match"
          statHeader="G/M"
        />
      </div>
    </Paper>
    // <SingleStatCard
    //   playersWithStat=weeklyGoalsScoredPerMatch
    //   statName="Goals Conceded per Match"
    //   statHeader="GC/M"
    // />
    // <SingleStatCard
    //   playersWithStat=weeklyEloDifference
    //   statName="Elo Difference"
    //   statHeader="+/-"
    // />
  </>;
};
