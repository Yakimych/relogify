[@react.component]
let make = (~communityName: string) => {
  let (getMostUsedPlayer, _) = StorageUtils.useMostUsedPlayer(communityName);

  getMostUsedPlayer()
  ->Belt.Option.mapWithDefault(React.null, playerName =>
      <RouteLink
        className="app-header-item"
        toPage={PlayerHome(communityName, playerName)}>
        {React.string("My Stats")}
      </RouteLink>
    );
};
