open Types;

module StringMap = Map.Make(String);

type leaderboardRow = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
};

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

let getLeaderboard = (results: list(result)): list(leaderboardRow) => {
  let leaderboardMap: StringMap.t(leaderboardRow) = StringMap.empty;
  // |> StringMap.add(
  //      "asd",
  //      {
  //        playerName: "asd",
  //        matchesWon: 0,
  //        matchesLost: 0,
  //        goalsScored: 0,
  //        goalsConceded: 0,
  //      },
  //    );

  leaderboardMap |> StringMap.bindings |> List.map(((_, v)) => v);
};
