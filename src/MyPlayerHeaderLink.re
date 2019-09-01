[@react.component]
let make = (~communityName: string) => {
  let (getMostUsedPlayer, _) = StorageUtils.useMostUsedPlayer(communityName);

  getMostUsedPlayer()
  ->Belt.Option.mapWithDefault(ReasonReact.null, playerName =>
      <RouteLink
        className="app-header-item"
        toPage={PlayerHome(communityName, playerName)}>
        {ReasonReact.string("My Stats")}
      </RouteLink>
    );
};
