type page =
  | Home
  | CreateCommunityPage
  | CommunityStart(string)
  | CommunityAdmin(string)
  | History(string)
  | TopX(string)
  | PlayerHome(string, string)
  | HeadToHead(string, string, string);

type player = {name: string};

type result = {
  id: int,
  player1: player,
  player2: player,
  player1goals: int,
  player2goals: int,
  date: Js.Date.t,
  extratime: bool,
};

type playerStats = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
};

type streak = {
  results: list(result),
  endingResult: option(result),
};

let numberOfMatches = (streak: streak) => streak.results->Belt.List.length;

let startedAt = (streak: streak) =>
  streak.results->Belt.List.reverse->Belt.List.headExn.date;

// TODO: Merge endedAt and endedBy and return a Tuple/type?
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
