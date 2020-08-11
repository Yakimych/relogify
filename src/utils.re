open Types;

let text = React.string;

let getCurrentWeek = () => {
  let startDate =
    Js.Date.make()
    ->DateFns.startOfWeekOpt({locale: None, weekStartsOn: Some(1)});
  (startDate, startDate->DateFns.addWeeks(1));
};

let resultsByDate = (first: matchResult, second: matchResult) =>
  DateFns.compareAsc(first.date, second.date);

let formatDate = (date: Js.Date.t) => date->DateFns.format("yyyy-MM-dd");
let formatDateTime = (date: Js.Date.t) =>
  date->DateFns.format("yyyy-MM-dd HH:mm");
let formatDateTimeSeconds = (date: Js.Date.t) =>
  date->DateFns.format("yyyy-MM-dd HH:mm:ss");

let withCurrentTime = (date: Js.Date.t, now: Js.Date.t) =>
  date
  ->DateFns.setHours(DateFns.getHours(now))
  ->DateFns.setMinutes(DateFns.getMinutes(now))
  ->DateFns.setSeconds(DateFns.getSeconds(now));

let toJsonDate = (date: Js.Date.t): Js.Json.t =>
  date |> Js.Date.toISOString |> Js.Json.string;

let validNumberOfGoals = (goalsString: string): int =>
  try(int_of_string(goalsString) |> Js.Math.max_int(0)) {
  | Failure(_) => 0
  };

let takeMax = (list, maxNumberToTake) =>
  list->Belt.List.take(maxNumberToTake)->Belt.Option.getWithDefault(list);

let distinctStrings = (strings: array(string)) =>
  strings->Belt.Set.String.fromArray->Belt.Set.String.toArray;
