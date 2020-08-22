open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path->Belt.List.map(Js.Global.decodeURI)) {
  | [] =>
    <MaterialUi.Container maxWidth=`Sm> <IntroPage /> </MaterialUi.Container>
  | ["new"] =>
    <MaterialUi.Container maxWidth=`Sm>
      <CreateCommunityPage />
    </MaterialUi.Container>
  | [communityName, "admin", ...subRoute] =>
    <MaterialUi.Container maxWidth=`Lg>
      <CommunityAdminLoginPage communityName subRoute />
    </MaterialUi.Container>
  | [communityName, ...subRoute] =>
    switch (subRoute) {
    | [] =>
      <MaterialUi.Container maxWidth=`Sm>
        <CommunityStartPage communityName />
      </MaterialUi.Container>
    | ["top"] =>
      <MaterialUi.Container maxWidth=`Lg>
        <TopBoard communityName />
      </MaterialUi.Container>
    | ["history"] =>
      <MaterialUi.Container maxWidth=`Sm>
        <ResultHistory communityName />
      </MaterialUi.Container>
    | [playerName] =>
      <MaterialUi.Container maxWidth=`Sm>
        <PlayerResults communityName playerName />
      </MaterialUi.Container>
    | [player1Name, player2Name] =>
      <MaterialUi.Container maxWidth=`Sm>
        <HeadToHeadPage communityName player1Name player2Name />
      </MaterialUi.Container>
    | _ =>
      <MaterialUi.Container maxWidth=`Sm>
        <div> {text("Invalid route")} </div>
      </MaterialUi.Container>
    }
  };
};
