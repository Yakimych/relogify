// TODO: bs-date-fns or re-date?
let formatDate = (date: Js.Date.t) =>
  Js.Date.toISOString(date)->String.sub(0, 10);
