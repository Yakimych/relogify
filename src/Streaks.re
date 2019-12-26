open Types;
open Utils;

let startNewStreakWithResult = (result: matchResult, streaks: list(streak)) => [
  {results: [result], endingResult: None},
  ...streaks,
];

let addResultToCurrentStreak = (result: matchResult, streaks: list(streak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: [result, ...currentStreak.results], endingResult: None},
    ...streaks->Belt.List.tailExn,
  ];
};

let setEndingResult = (result: matchResult, streaks: list(streak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: currentStreak.results, endingResult: Some(result)},
    ...streaks->Belt.List.tailExn,
  ];
};

let resultStreakReducer =
    (playerName: string, streaks: list(streak), result: matchResult)
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
    (playerName: string, results: list(matchResult)): list(streak) =>
  results
  ->Belt.List.sort(resultsByDate)
  ->Belt.List.reduce([], resultStreakReducer(playerName));

let emptyStreak = {results: [], endingResult: None};

let getLongestStreak = (streaks: list(streak)): option(streak) =>
  streaks
  ->Belt.List.keep(s => s.endingResult->Belt.Option.isSome)
  ->Belt.List.reduce(None, (longestStreak, currentStreak) =>
      Belt.List.length(currentStreak.results)
      >= longestStreak->Belt.Option.mapWithDefault(0, s =>
           s.results->Belt.List.length
         )
        ? Some(currentStreak) : longestStreak
    );

let getCurrentStreak = (streaks: list(streak)): option(streak) =>
  streaks
  ->Belt.List.keep(s => s.endingResult->Belt.Option.isNone)
  ->Belt.List.head;
