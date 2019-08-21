open Types;

let startNewStreakWithResult = (result: result, streaks: list(streak)) => [
  {results: [result], endingResult: None},
  ...streaks,
];

let addResultToCurrentStreak = (result: result, streaks: list(streak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: [result, ...currentStreak.results], endingResult: None},
    ...streaks->Belt.List.tailExn,
  ];
};

let setEndingResult = (result: result, streaks: list(streak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: currentStreak.results, endingResult: Some(result)},
    ...streaks->Belt.List.tailExn,
  ];
};

let resultStreakReducer =
    (playerName: string, streaks: list(streak), result: result)
    : list(streak) => {
  let isWin =
    result.player1.name == playerName
    && result.player1goals > result.player2goals
    || result.player2.name == playerName
    && result.player1goals < result.player2goals;

  streaks
  ->Belt.List.head
  ->Belt.Option.mapWithDefault(
      isWin ? streaks |> startNewStreakWithResult(result) : [], currentStreak =>
      switch (isWin, currentStreak.endingResult) {
      | (true, Some(_)) => streaks |> startNewStreakWithResult(result)
      | (true, None) => streaks |> addResultToCurrentStreak(result)
      | (false, Some(_)) => streaks
      | (false, None) => streaks |> setEndingResult(result)
      }
    );
};

let getAllStreaks =
    (playerName: string, results: list(result)): list(streak) =>
  results->Belt.List.reduce([], resultStreakReducer(playerName));