open Types;

let getUrl = (page: page): string =>
  switch (page) {
  | Home => "/"
  | CreateCommunityPage => "/new"
  | AdminSettingsPage(communityName) =>
    "/" ++ communityName ++ "/admin/settings"
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
      ~className: string=?,
      ~style: ReactDOMRe.Style.t=?,
      ~children: React.element,
    ) =>
  <Link className url={getUrl(toPage)} style> children </Link>;
