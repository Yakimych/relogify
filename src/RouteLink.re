open Types;

let getUrl = (page: page): string =>
  switch (page) {
  | Home => "/"
  | CommunityStart(communityName) => "/" ++ communityName
  | History(communityName) => "/" ++ communityName ++ "/history"
  | PlayerHome(communityName, playerName) =>
    "/" ++ communityName ++ "/" ++ playerName
  | HeadToHead(communityName, player1Name, player2Name) =>
    "/" ++ communityName ++ "/" ++ player1Name ++ "/" ++ player2Name
  };

[@react.component]
let make =
    (~toPage: page, ~style: ReactDOMRe.Style.t=?, ~children: React.element) =>
  <Link url={getUrl(toPage)} style> children </Link>;
