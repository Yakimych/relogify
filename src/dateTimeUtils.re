module Datetime = {
  type t = Js.Date.t;
  let parse: string => t = Js.Date.fromString;
  let serialize: t => string = Js.Date.toISOString;
};
