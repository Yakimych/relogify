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
        isWin ? [{results: [result], endingResult: None}] : [],
        currentStreak =>
        switch (isWin, currentStreak.endingResult) {
        | (true, Some(_)) => [
            {results: [result], endingResult: None},
            ...state,
          ]
        | (true, None) => [
            {
              results: [result, ...currentStreak.results],
              endingResult: None,
            },
            ...state->Belt.List.tailExn,
          ]
        | (false, Some(_)) => state
        | (false, None) => [
            {results: currentStreak.results, endingResult: Some(result)},
            ...state->Belt.List.tailExn,
          ]
        }
      );
  };

  let finalState: list(tempStreak) =
    results->Belt.List.reduce(initialState, reduceFunc);

  finalState;
};
