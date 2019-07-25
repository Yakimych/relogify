[@react.component]
let make = (~communityName, ~player1Name, ~player2Name) =>
  <div>
    <h1> {ReasonReact.string("Head to head in " ++ communityName)} </h1>
    <div> {ReasonReact.string("Player1: " ++ player1Name)} </div>
    <div> {ReasonReact.string("Player2: " ++ player2Name)} </div>
  </div>;
