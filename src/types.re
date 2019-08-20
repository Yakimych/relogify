type player = {name: string};

type result = {
  id: int,
  player1: player,
  player2: player,
  player1goals: int,
  player2goals: int,
  date: string,
  extratime: bool,
};

type streak = {
  results: list(result),
  endingResult: option(result),
};

let numberOfMatches = (streak: streak) => streak.results->Belt.List.length;

let startedAt = (streak: streak) =>
  streak.results->Belt.List.reverse->Belt.List.headExn.date;

// TODO: Merge endedAt and endedBy and return a Tuple?
let endedAt = (streak: streak) =>
  streak.endingResult->Belt.Option.map(r => r.date);

let endedBy = (streak: streak, playerName: string) =>
  streak.endingResult
  ->Belt.Option.map(r =>
      r.player1.name === playerName ? r.player2 : r.player1
    );

type streaks = {
  longestStreak: option(streak),
  currentStreak: option(streak),
};
