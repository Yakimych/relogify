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
  | [communityName, ...subRoute] => <CommunityRoute communityName subRoute />
  };
};
