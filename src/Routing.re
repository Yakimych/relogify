open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path->Belt.List.map(Js.Global.decodeURI)) {
  | [] => <Container maxWidth="sm"> <IntroPage /> </Container>
  | ["new"] => <Container maxWidth="sm"> <CreateCommunityPage /> </Container>
  | [communityName] =>
    <Container maxWidth="sm"> <CommunityStartPage communityName /> </Container>
  | [communityName, "top"] =>
    <Container maxWidth="lg"> <TopBoard communityName /> </Container>
  | [communityName, "history"] =>
    <Container maxWidth="sm"> <ResultHistory communityName /> </Container>
  | [communityName, playerName] =>
    <Container maxWidth="sm">
      <PlayerResults communityName playerName />
    </Container>
  | [communityName, player1Name, player2Name] =>
    <Container maxWidth="sm">
      <HeadToHeadPage communityName player1Name player2Name />
    </Container>
  | _ =>
    <Container maxWidth="sm">
      <div> {text("Invalid route")} </div>
    </Container>
  };
};
