open Types;

let emptyPlayerStats = (playerName: string) => {
  playerName,
  goalsScored: 0,
  goalsConceded: 0,
  matchesWon: 0,
  matchesLost: 0,
};

let playerStatsReducer =
    (playerName: string, stats: playerStats, result: matchResult): playerStats =>
  if (result.player1.name !== playerName && result.player2.name !== playerName) {
    stats;
  } else {
    let goalsScoredThisMatch =
      result.player1.name === playerName
        ? result.player1goals : result.player2goals;
    let goalsConcededThisMatch =
      result.player1.name === playerName
        ? result.player2goals : result.player1goals;

    {
      ...stats,
      goalsScored: stats.goalsScored + goalsScoredThisMatch,
      goalsConceded: stats.goalsConceded + goalsConcededThisMatch,
      matchesWon:
        stats.matchesWon
        + (goalsScoredThisMatch > goalsConcededThisMatch ? 1 : 0),
      matchesLost:
        stats.matchesLost
        + (goalsScoredThisMatch > goalsConcededThisMatch ? 0 : 1),
    };
  };

let getPlayerStats =
    (playerName: string, results: list(matchResult)): playerStats =>
  results->Belt.List.reduce(
    emptyPlayerStats(playerName),
    playerStatsReducer(playerName),
  );
