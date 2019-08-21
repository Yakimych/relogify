open Types;

type leaderboardRow = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
};

let byName = (a, b) => String.compare(a.playerName, b.playerName);

let goalDiff = (row: leaderboardRow) => row.goalsScored - row.goalsConceded;

let matchesWonPerPlayed = (row: leaderboardRow) =>
  float_of_int(row.matchesWon)
  /. float_of_int(row.matchesWon + row.matchesLost);

let goalsScoredPerMatch = (row: leaderboardRow) =>
  float_of_int(row.goalsScored)
  /. float_of_int(row.matchesWon + row.matchesLost);

let goalsConcededPerMatch = (row: leaderboardRow) =>
  float_of_int(row.goalsConceded)
  /. float_of_int(row.matchesWon + row.matchesLost);

let emptyRow = (playerName: string) => {
  playerName,
  matchesWon: 0,
  matchesLost: 0,
  goalsScored: 0,
  goalsConceded: 0,
};

let updateRow = (row: leaderboardRow, goalsScored: int, goalsConceded: int) => {
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
    (leaderboardMap: Belt_MapString.t(leaderboardRow), result: result)
    : Belt_MapString.t(leaderboardRow) => {
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

let getLeaderboard = (results: list(result)): list(leaderboardRow) =>
  results->Belt.List.reduce(Belt_MapString.empty, leaderboardReducer)
  |> Belt_MapString.toList
  |> List.map(((_, v)) => v);
