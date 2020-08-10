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
    // TODO: Extract TopBoard to top level, since it is going to be subscription-based anyway?
    | ["top"] =>
      <MaterialUi.Container maxWidth=`Lg>
        <div> {text("PLACEHOLDER FOR TOPBOARD: " ++ communityName)} </div>
      </MaterialUi.Container>
    // <TopBoard communityName />
    // TODO: Parametrize the history route
    // | ["history", startYear, startMonth, startDay, endYear, endMonth, endDay] =>
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
