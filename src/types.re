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
