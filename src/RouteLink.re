open Types;

let getUrl = (page: page): string =>
  switch (page) {
  | Home => "/"
  | CreateCommunityPage => "/new"
  | AdminSettingsPage(communityName) =>
    "/" ++ communityName ++ "/admin/settings"
  | AdminPlayersPage(communityName) =>
    "/" ++ communityName ++ "/admin/players"
  | AdminResultsPage(communityName) =>
    "/" ++ communityName ++ "/admin/results"
  | CommunityStart(communityName) => "/" ++ communityName
  | CommunityAdmin(communityName) => "/" ++ communityName ++ "/admin"
  | TopX(communityName) => "/" ++ communityName ++ "/top"
  | History(communityName) => "/" ++ communityName ++ "/history"
  | PlayerHome(communityName, playerName) =>
    "/" ++ communityName ++ "/" ++ playerName
  | HeadToHead(communityName, player1Name, player2Name) =>
    "/" ++ communityName ++ "/" ++ player1Name ++ "/" ++ player2Name
  };

[@react.component]
let make =
    (
      ~toPage: page,
      ~className: option(string)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      ~children: React.element,
    ) =>
  <MaterialUi.Link
    ?className onClick={_ => ReasonReactRouter.push(getUrl(toPage))} ?style>
    children
  </MaterialUi.Link>;
