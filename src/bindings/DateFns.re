[@bs.module]
external format: (Js.Date.t, string) => string = "date-fns/format";

[@bs.module]
external setSeconds: (Js.Date.t, float) => Js.Date.t = "date-fns/set_seconds";

[@bs.module]
external setMinutes: (Js.Date.t, float) => Js.Date.t = "date-fns/set_minutes";

[@bs.module]
external setHours: (Js.Date.t, float) => Js.Date.t = "date-fns/set_hours";

[@bs.module] external getSeconds: Js.Date.t => float = "date-fns/get_seconds";
[@bs.module] external getMinutes: Js.Date.t => float = "date-fns/get_minutes";
[@bs.module] external getHours: Js.Date.t => float = "date-fns/get_hours";

[@bs.module]
external addWeeks: (Js.Date.t, float) => Js.Date.t = "date-fns/add_weeks";

[@bs.module]
external startOfWeek: (Js.Date.t, {. "weekStartsOn": int}) => Js.Date.t =
  "date-fns/start_of_week";

[@bs.module] external isMonday: Js.Date.t => bool = "date-fns/is_monday";
