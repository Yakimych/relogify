[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    <div>
      {ReasonReact.string("url parts: ")}
      {url.path
       |> List.map(p => <div> {ReasonReact.string(p)} </div>)
       |> Array.of_list
       |> ReasonReact.array}
    </div>
    <>
      {switch (url.path) {
       | [communityName] => <CommunityStartPage communityName />
       | [communityName, playerName] =>
         <PlayerResultsPage communityName playerName />
       | [communityName, player1Name, player2Name] =>
         <HeadToHeadPage communityName player1Name player2Name />
       | _ => <div> {ReasonReact.string("Invalid route")} </div>
       }}
    </>
  </div>;
};
