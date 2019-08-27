open EloUtils;
open BsRecharts;

[@react.component]
let make =
    (~playerName: string, ~resultsWithRatings: list(resultWithRatings)) => {
  let data =
    resultsWithRatings
    ->Belt.List.keep(r =>
        r.result.player1.name === playerName
        || r.result.player2.name === playerName
      )
    ->Belt.List.map(r =>
        {
          "date": r.result.date,
          "rating":
            Js.Math.round(
              r.result.player1.name === playerName
                ? r.player1RatingAfter : r.player2RatingAfter,
            ),
        }
      )
    ->Belt.List.reverse
    ->Belt.List.toArray;

  <>
    <ResponsiveContainer height={Px(300.0)} width={Px(500.)}>
      <LineChart data>
        <CartesianGrid />
        <XAxis dataKey="date" />
        <YAxis />
        <Tooltip />
        <Line _type=`monotone dataKey="rating" stroke="#8884d8" />
      </LineChart>
    </ResponsiveContainer>
  </>;
};
