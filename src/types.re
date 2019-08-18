type player = {name: string};

type streak = {
  // TODO: Discriminated union?
  numberOfMatches: int,
  startedAt: Js.Date.t,
  endedAt: option(Js.Date.t),
  endedBy: option(player),
};

type streaks = {
  longestStreak: option(streak),
  currentStreak: option(streak),
};

type result = {
  id: int,
  player1: player,
  player2: player,
  player1goals: int,
  player2goals: int,
  date: string,
  extratime: bool,
};
