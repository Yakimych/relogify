open Types;

let getPlayerStats = (playerName: string, results: list(result)): playerStats => {
  playerName,
  goalsScored: 0,
  goalsConceded: 0,
  matchesWon: 0,
  matchesLost: 0,
};
