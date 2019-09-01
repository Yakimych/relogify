[@react.component]
let make = (~communityName: string) => {
  let (mostUsedPlayerRef, _) = StorageUtils.useMostUsedPlayer(communityName);

  mostUsedPlayerRef
  ->React.Ref.current
  ->Js.Nullable.toOption
  ->Belt.Option.mapWithDefault(ReasonReact.null, playerName =>
      <RouteLink
        className="app-header-item"
        toPage={PlayerHome(communityName, playerName)}>
        {ReasonReact.string("My Stats")}
      </RouteLink>
    );
};
