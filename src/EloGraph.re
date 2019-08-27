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
    ->Belt.List.map(r => {"rating": Js.Math.round(r.player1RatingAfter)})
    ->Belt.List.toArray;

  <>
    <ResponsiveContainer height={Px(200.0)} width={Px(300.)}>
      <LineChart data>
        <CartesianGrid />
        <XAxis dataKey="rating" />
        <YAxis />
        <Tooltip />
        <Legend />
        <Line _type=`monotone dataKey="rating" stroke="#8884d8" />
      </LineChart>
    </ResponsiveContainer>
  </>;
};
