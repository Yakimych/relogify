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

type tempStreak = {
  results: array(result),
  endingResult: option(result),
};

let reduceFunc =
    (state: array(tempStreak), result: result): array(tempStreak) => {
  state;
};

let getAllStreaks = (results: array(result)): array(tempStreak) => {
  let initialState: array(tempStreak) = [||];

  let finalState: array(tempStreak) =
    results->Belt.Array.reduce(initialState, reduceFunc);

  finalState;
};
