// TODO: bs-date-fns or re-date?
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
