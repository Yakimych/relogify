open Utils;
open LeaderboardUtils;

let toStringRating = (rating: float) =>
  rating |> Js.Math.round |> int_of_float |> string_of_int;

[@react.component]
let make = (~ratingBefore: float, ~ratingAfter: float, ~onClick) => {
  let ratingDiff =
    Js.Math.round(ratingAfter) -. Js.Math.round(ratingBefore) |> int_of_float;

  <span
    className="rating"
    onClick
    title={(ratingBefore |> toStringRating) ++ formatDiff(ratingDiff)}>
    {text("(" ++ (ratingAfter |> toStringRating) ++ ")")}
  </span>;
};
