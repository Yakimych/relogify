open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <Container maxWidth="md">
    {switch (url.path->Belt.List.map(Js.Global.decodeURI)) {
     | [] => <IntroPage />
     | [communityName] => <CommunityStartPage communityName />
     | [communityName, "history"] => <ResultHistory communityName />
     | [communityName, playerName] =>
       <PlayerResults communityName playerName />
     | [communityName, player1Name, player2Name] =>
       <HeadToHeadPage communityName player1Name player2Name />
     | _ => <div> {text("Invalid route")} </div>
     }}
  </Container>;
};
