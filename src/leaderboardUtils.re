open Types;
open PlayerStatsUtils;

type columnType =
  | EloRating(EloUtils.eloMap)
  | WinsPerMatch
  | MatchesWon
  | MatchesLost
  | GoalsScored
  | GoalsConceded
  | GoalDiff
  | GoalsScoredPerMatch
  | GoalsConcededPerMatch;

type sortDirection = [ | `Asc | `Desc];

let sortCompare = (a, b) =>
  if (a > b) {
    1;
  } else if (a < b) {
    (-1);
  } else {
    0;
  };

let sortCompareDesc = (a, b) => - sortCompare(a, b);

type playerStatsMap = Belt_MapString.t(playerStats);

let byName = (a, b) => String.compare(a.playerName, b.playerName);

let goalDiff = (row: playerStats) => row.goalsScored - row.goalsConceded;

let totalMatchesPlayed = (row: playerStats) =>
  row.matchesWon + row.matchesLost + row.matchesDrawn;

let minMatchesForStats = 0;

let includedInStats = (stats: playerStats) =>
  totalMatchesPlayed(stats) >= minMatchesForStats;

let formatPercentage = (value: float) =>
  (value |> int_of_float |> string_of_int) ++ "%";

let formatDiff = (diff: int) => (diff > 0 ? "+" : "") ++ string_of_int(diff);

let formatGoalsPerMatch = (goals: float) =>
  Js.Float.toFixedWithPrecision(goals, ~digits=1);

let matchesWonPerPlayed = (row: playerStats) =>
  Js.Math.round(
    float_of_int(row.matchesWon)
    /. float_of_int(row |> totalMatchesPlayed)
    *. 100.0,
  );

let goalsScoredPerMatch = (row: playerStats) =>
  float_of_int(row.goalsScored) /. float_of_int(row |> totalMatchesPlayed);

let goalsConcededPerMatch = (row: playerStats) =>
  float_of_int(row.goalsConceded) /. float_of_int(row |> totalMatchesPlayed);

let emptyRow = (playerName: string) => {
  playerName,
  matchesWon: 0,
  matchesLost: 0,
  matchesDrawn: 0,
  goalsScored: 0,
  goalsConceded: 0,
};

let updateRow = (row: playerStats, goalsScored: int, goalsConceded: int) => {
  playerName: row.playerName,
  matchesWon: row.matchesWon + (isWin(goalsScored, goalsConceded) ? 1 : 0),
  matchesLost: row.matchesLost + (isLoss(goalsScored, goalsConceded) ? 1 : 0),
  matchesDrawn:
    row.matchesDrawn + (isDraw(goalsScored, goalsConceded) ? 1 : 0),
  goalsScored: row.goalsScored + goalsScored,
  goalsConceded: row.goalsConceded + goalsConceded,
};

let leaderboardReducer =
    (leaderboardMap: playerStatsMap, result: matchResult): playerStatsMap => {
  let player1Row =
    leaderboardMap->Belt_MapString.getWithDefault(
      result.player1.name,
      emptyRow(result.player1.name),
    );

  let player2Row =
    leaderboardMap->Belt_MapString.getWithDefault(
      result.player2.name,
      emptyRow(result.player2.name),
    );

  leaderboardMap
  ->Belt_MapString.set(
      result.player1.name,
      updateRow(player1Row, result.player1goals, result.player2goals),
    )
  ->Belt_MapString.set(
      result.player2.name,
      updateRow(player2Row, result.player2goals, result.player1goals),
    );
};

let getLeaderboard = (results: list(matchResult)): list(playerStats) =>
  results->Belt.List.reduce(Belt_MapString.empty, leaderboardReducer)
  |> Belt_MapString.toList
  |> List.map(((_, v)) => v);
