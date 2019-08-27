open Types;

type playerStatsMap = Belt_MapString.t(playerStats);

let byName = (a, b) => String.compare(a.playerName, b.playerName);

let goalDiff = (row: playerStats) => row.goalsScored - row.goalsConceded;

let minMatchesForStats = 0;
let includedInStats = (stats: playerStats) =>
  stats.matchesWon + stats.matchesLost >= minMatchesForStats;

let formatPercentage = (value: float) =>
  (value |> int_of_float |> string_of_int) ++ "%";

let formatDiff = (diff: int) => (diff > 0 ? "+" : "") ++ string_of_int(diff);

let formatGoalsPerMatch = (goals: float) =>
  Js.Float.toFixedWithPrecision(goals, ~digits=1);

let matchesWonPerPlayed = (row: playerStats) =>
  Js.Math.round(
    float_of_int(row.matchesWon)
    /. float_of_int(row.matchesWon + row.matchesLost)
    *. 100.0,
  );

let goalsScoredPerMatch = (row: playerStats) =>
  float_of_int(row.goalsScored)
  /. float_of_int(row.matchesWon + row.matchesLost);

let goalsConcededPerMatch = (row: playerStats) =>
  float_of_int(row.goalsConceded)
  /. float_of_int(row.matchesWon + row.matchesLost);

let emptyRow = (playerName: string) => {
  playerName,
  matchesWon: 0,
  matchesLost: 0,
  goalsScored: 0,
  goalsConceded: 0,
};

let updateRow = (row: playerStats, goalsScored: int, goalsConceded: int) => {
  let isWin = goalsScored > goalsConceded;

  {
    ...row,
    matchesWon: row.matchesWon + (isWin ? 1 : 0),
    matchesLost: row.matchesLost + (isWin ? 0 : 1),
    goalsScored: row.goalsScored + goalsScored,
    goalsConceded: row.goalsConceded + goalsConceded,
  };
};

let leaderboardReducer =
    (leaderboardMap: playerStatsMap, result: result): playerStatsMap => {
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

let getLeaderboard = (results: list(result)): list(playerStats) =>
  results->Belt.List.reduce(Belt_MapString.empty, leaderboardReducer)
  |> Belt_MapString.toList
  |> List.map(((_, v)) => v);
