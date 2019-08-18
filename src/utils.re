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

    let maybeCurrentStreak = state->Belt.List.head;
    let currentStreakHasEnded =
      maybeCurrentStreak->Belt.Option.mapWithDefault(false, s =>
        s.endingResult->Belt.Option.isSome
      );

    /* TODO: Pattern matching? */
    if (isWin) {
      if (currentStreakHasEnded) {
        [{results: [result], endingResult: None}, ...state];
      } else {
        [
          {
            results: [
              result,
              /* TODO: Do we actually know at this point that currentStreak is Some? */
              ...maybeCurrentStreak->Belt.Option.mapWithDefault([], s =>
                   s.results
                 ),
            ],
            endingResult: None,
          },
          ...state->Belt.List.tail->Belt.Option.getWithDefault([]),
        ];
      };
    } else if (maybeCurrentStreak->Belt.Option.mapWithDefault(true, s =>
                 s.endingResult->Belt.Option.isSome
               )) {
      state;
    } else {
      [
        // Add current result as streak-ending result to current streak
        {
          results:
            maybeCurrentStreak->Belt.Option.mapWithDefault([], s => s.results),
          endingResult: Some(result),
        },
        ...state->Belt.List.tail->Belt.Option.getWithDefault([]),
      ];
    };
  };

  let finalState: list(tempStreak) =
    results->Belt.List.reduce(initialState, reduceFunc);

  finalState;
};
