open Types;

let text = ReasonReact.string;

let formatDate = (date: Js.Date.t) => date->DateFns.format("YYYY-MM-DD");
let formatDateTime = (date: Js.Date.t) =>
  date->DateFns.format("YYYY-MM-DD HH:mm");
let formatDateTimeSeconds = (date: Js.Date.t) =>
  date->DateFns.format("YYYY-MM-DD HH:mm:ss");

let withCurrentTime = (date: Js.Date.t, now: Js.Date.t) =>
  date
  ->DateFns.setHours(DateFns.getHours(now))
  ->DateFns.setMinutes(DateFns.getMinutes(now))
  ->DateFns.setSeconds(DateFns.getSeconds(now));

[@bs.deriving jsConverter]
type tempStreak = {
  results: list(result),
  endingResult: option(result),
};

let startNewStreakWithResult = (result: result, streaks: list(tempStreak)) => [
  {results: [result], endingResult: None},
  ...streaks,
];

let addResultToCurrentStreak = (result: result, streaks: list(tempStreak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: [result, ...currentStreak.results], endingResult: None},
    ...streaks->Belt.List.tailExn,
  ];
};

let setEndingResult = (result: result, streaks: list(tempStreak)) => {
  let currentStreak = streaks->Belt.List.headExn;
  [
    {results: currentStreak.results, endingResult: Some(result)},
    ...streaks->Belt.List.tailExn,
  ];
};

let getAllStreaks =
    (playerName: string, results: list(result)): list(tempStreak) => {
  let initialState: list(tempStreak) = [];

  let reduceFunc =
      (state: list(tempStreak), result: result): list(tempStreak) => {
    let isWin =
      result.player1.name == playerName
      && result.player1goals > result.player2goals
      || result.player2.name == playerName
      && result.player1goals < result.player2goals;

    state
    ->Belt.List.head
    ->Belt.Option.mapWithDefault(
        isWin ? state |> startNewStreakWithResult(result) : [], currentStreak =>
        switch (isWin, currentStreak.endingResult) {
        | (true, Some(_)) => state |> startNewStreakWithResult(result)
        | (true, None) => state |> addResultToCurrentStreak(result)
        | (false, Some(_)) => state
        | (false, None) => state |> setEndingResult(result)
        }
      );
  };

  let finalState: list(tempStreak) =
    results->Belt.List.reduce(initialState, reduceFunc);

  finalState;
};
