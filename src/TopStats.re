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

let byGoalsConceded = (r1, r2) =>
  switch (r1 |> goalsConcededPerMatch, r2 |> goalsConcededPerMatch) {
  | (a, b) when a == b => sortCompare(r1.goalsConceded, r2.goalsConceded)
  | (a, b) => sortCompare(a, b)
  };

let byTupleValue = ((_, r1), (_, r2)) =>
  switch (r1, r2) {
  | (a, b) when a == b => sortCompareDesc(r1, r2)
  | (a, b) => sortCompareDesc(a, b)
  };

// TODO: Fragment for results (within a date range)

module TopStatsFragment = [%relay.fragment
  {|
    fragment TopStatsColumn_ScoreType on community_settings @relay(plural: true) {
      score_type
    }
  |}
];

[@react.component]
let make =
    (
      ~scoreTypeFragment,
      ~title,
      ~resultsWithMap: temp_resultsWithRatingMap,
      ~startDate,
    ) => {
  let defaultCommunitySettings: TopStatsFragment.Types.fragment_t = {
    score_type: DefaultCommunitySettings.scoreType,
  };

  let scoreTypeFragment =
    TopStatsFragment.use(scoreTypeFragment)
    |> Utils.headWithDefault(defaultCommunitySettings);

  switch (
    resultsWithMap.resultsWithRatings
    ->Belt.List.keep(r => r.result.date >= startDate)
  ) {
  | [] => React.null
  | relevantResultsWithRatings =>
    let leaderboardRows =
      getLeaderboard(
        relevantResultsWithRatings->Belt.List.map(r => r.result),
      );

    let topWinPercentageRows =
      leaderboardRows
      ->Belt.List.sort(byWinPercentage)
      ->takeMax(topNumberOfRows)
      ->Belt.List.map(row =>
          (row.playerName, row |> matchesWonPerPlayed |> formatPercentage)
        );

    let topGoalsScoredPerMatchRows =
      leaderboardRows
      ->Belt.List.sort(byGoalsScored)
      ->takeMax(topNumberOfRows)
      ->Belt.List.map(row =>
          (row.playerName, row |> goalsScoredPerMatch |> formatGoalsPerMatch)
        );

    let topGoalsConcededPerMatchRows =
      leaderboardRows
      ->Belt.List.sort(byGoalsConceded)
      ->takeMax(topNumberOfRows)
      ->Belt.List.map(row =>
          (
            row.playerName,
            row |> goalsConcededPerMatch |> formatGoalsPerMatch,
          )
        );

    let topEloDiffRows =
      getRatingDiffs(resultsWithMap.ratingMap, relevantResultsWithRatings)
      ->Belt_MapString.toList
      ->Belt.List.sort(byTupleValue)
      ->takeMax(topNumberOfRows)
      ->Belt.List.map(((playerName, rating)) =>
          (playerName, rating |> Js.Math.round |> int_of_float |> formatDiff)
        );

    let texts = Texts.getScoreTypeTexts(scoreTypeFragment.score_type);

    <MaterialUi.Paper>
      <div className="title">
        <MaterialUi.Typography variant=`H6>
          {text(title)}
        </MaterialUi.Typography>
      </div>
      <div className="top-stats-container">
        <SingleStatCard
          playersWithStat=topWinPercentageRows
          statName="Win Percentage"
        />
        <SingleStatCard
          playersWithStat=topGoalsScoredPerMatchRows
          statName={texts.pointsWonPerMatch}
        />
        <SingleStatCard
          playersWithStat=topGoalsConcededPerMatchRows
          statName={texts.pointsLostPerMatch}
        />
        <SingleStatCard
          playersWithStat=topEloDiffRows
          statName="Elo Difference"
        />
      </div>
    </MaterialUi.Paper>;
  };
};
