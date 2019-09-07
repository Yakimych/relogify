open Types;
open DateFns;

let text = ReasonReact.string;

let getCurrentWeek = () => {
  let startDate = Js.Date.make()->startOfWeek({"weekStartsOn": 1});
  (startDate, startDate->addWeeks(1.0));
};

let resultsByDate = (first: result, second: result) =>
  DateFns.compareAsc(first.date, second.date);

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

let toJsonDate = (date: Js.Date.t): Js.Json.t =>
  date |> Js.Date.toISOString |> Js.Json.string;

let validNumberOfGoals = (goalsString: string): int =>
  try (int_of_string(goalsString) |> Js.Math.max_int(0)) {
  | Failure(_) => 0
  };

let widthLimit = 600;
let cellDisplay = pageWidth => pageWidth <= widthLimit ? "none" : "table-cell";

let getDimensions: unit => (int, int) = [%bs.raw
  {|
function getWindowDimensions() {
  return [
    window.innerWidth,
    window.innerHeight
  ];
}
|}
];
