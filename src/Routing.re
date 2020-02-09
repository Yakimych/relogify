open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path->Belt.List.map(Js.Global.decodeURI)) {
  | [] =>
    <MaterialUi_Container maxWidth=`Sm> <IntroPage /> </MaterialUi_Container>
  | ["new"] =>
    <MaterialUi_Container maxWidth=`Sm>
      <CreateCommunityPage />
    </MaterialUi_Container>
  | [communityName] =>
    <MaterialUi_Container maxWidth=`Sm>
      <CommunityStartPage communityName />
    </MaterialUi_Container>
  | [communityName, "admin", ...subRoute] =>
    <MaterialUi_Container maxWidth=`Lg>
      <CommunityAdminPage communityName subRoute />
    </MaterialUi_Container>
  | [communityName, "top"] =>
    <MaterialUi_Container maxWidth=`Lg>
      <TopBoard communityName />
    </MaterialUi_Container>
  | [communityName, "history"] =>
    <MaterialUi_Container maxWidth=`Sm>
      <ResultHistory communityName />
    </MaterialUi_Container>
  | [communityName, playerName] =>
    <MaterialUi_Container maxWidth=`Sm>
      <PlayerResults communityName playerName />
    </MaterialUi_Container>
  | [communityName, player1Name, player2Name] =>
    <MaterialUi_Container maxWidth=`Sm>
      <HeadToHeadPage communityName player1Name player2Name />
    </MaterialUi_Container>
  | _ =>
    <MaterialUi_Container maxWidth=`Sm>
      <div> {text("Invalid route")} </div>
    </MaterialUi_Container>
  };
};
