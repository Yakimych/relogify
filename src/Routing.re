[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    <div> {ReasonReact.string("Result log")} </div>
    <>
      {switch (url.path) {
       | [] => <Home />
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
