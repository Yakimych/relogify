open Types;

let emptyPlayerStats = (playerName: string) => {
  playerName,
  goalsScored: 0,
  goalsConceded: 0,
  matchesWon: 0,
  matchesLost: 0,
  matchesDrawn: 0,
};

let isWin = (goalsScored, goalsConceded) => goalsScored > goalsConceded;
let isLoss = (goalsScored, goalsConceded) => goalsScored < goalsConceded;
let isDraw = (goalsScored, goalsConceded) => goalsScored === goalsConceded;

let playerStatsReducer_old =
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
      playerName: stats.playerName,
      goalsScored: stats.goalsScored + goalsScoredThisMatch,
      goalsConceded: stats.goalsConceded + goalsConcededThisMatch,
      matchesWon:
        stats.matchesWon
        + (isWin(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
      matchesLost:
        stats.matchesLost
        + (isLoss(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
      matchesDrawn:
        stats.matchesDrawn
        + (isDraw(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
    };
  };

let playerStatsReducer =
    (
      playerName: string,
      stats: playerStats,
      result: PlayerResultsQuery_graphql.Types.response_results_connection_edges_node,
    )
    : playerStats =>
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
      playerName: stats.playerName,
      goalsScored: stats.goalsScored + goalsScoredThisMatch,
      goalsConceded: stats.goalsConceded + goalsConcededThisMatch,
      matchesWon:
        stats.matchesWon
        + (isWin(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
      matchesLost:
        stats.matchesLost
        + (isLoss(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
      matchesDrawn:
        stats.matchesDrawn
        + (isDraw(goalsScoredThisMatch, goalsConcededThisMatch) ? 1 : 0),
    };
  };

let getPlayerStats = (playerName: string, results): playerStats =>
  results->Belt.List.reduce(
    emptyPlayerStats(playerName),
    playerStatsReducer(playerName),
  );

let getPlayerStats_old =
    (playerName: string, results: list(matchResult)): playerStats =>
  results->Belt.List.reduce(
    emptyPlayerStats(playerName),
    playerStatsReducer_old(playerName),
  );

let hasPlayer1Won = (result: matchResult) =>
  isWin(result.player1goals, result.player2goals);

let hasPlayer2Won = (result: matchResult) =>
  isWin(result.player2goals, result.player1goals);

let hasMainPlayerWon = (mainPlayerName: option(string), result: matchResult) => {
  let player1Won = hasPlayer1Won(result);
  let player2Won = hasPlayer2Won(result);
  let mainPlayerWon =
    player1Won
    && mainPlayerName === Some(result.player1.name)
    || player2Won
    && mainPlayerName === Some(result.player2.name);

  mainPlayerWon;
};
