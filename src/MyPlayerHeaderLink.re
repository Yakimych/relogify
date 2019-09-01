[@react.component]
let make = (~communityName: string) =>
  StorageUtils.getMostOftenSavedPlayerName(communityName)
  ->Belt.Option.mapWithDefault(ReasonReact.null, playerName =>
      <RouteLink toPage={PlayerHome(communityName, playerName)}>
        {ReasonReact.string("My Stats")}
      </RouteLink>
    );
