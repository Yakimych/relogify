[@react.component]
let make = (~communityName, ~playerName) =>
  <div>
    <h1> {ReasonReact.string("Player results for " ++ playerName)} </h1>
    <div> {ReasonReact.string("Communty: " ++ communityName)} </div>
  </div>;
