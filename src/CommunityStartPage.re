[@react.component]
let make = (~communityName) =>
  <div>
    {ReasonReact.string("Community: " ++ communityName)}
    <AddResult />
  </div>;
