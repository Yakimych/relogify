open Dom.Storage2;

let addedPlayersKey = communityName => "added_players_" ++ communityName;

let byValue = ((_, v1), (_, v2)) => v2 - v1;

let getPlayerDict = communityName => {
  localStorage
  ->getItem(communityName |> addedPlayersKey)
  ->Belt.Option.mapWithDefault(Js.Dict.empty(), d =>
      d |> Js.Json.parseExn |> Json.Decode.dict(Json.Decode.int)
    );
};

let getMostOftenSavedPlayerName = (communityName): option(string) =>
  getPlayerDict(communityName)
  ->Js.Dict.entries
  ->Belt.List.fromArray
  ->Belt.List.keep(((_, v)) => v > 1)
  ->Belt.List.sort(byValue)
  ->Belt.List.map(((k, _)) => k)
  ->Belt.List.head;

let updatePlayersAfterAddingResult = (communityName, player1Name, player2Name) => {
  let savedDict = getPlayerDict(communityName);

  let player1TimesSaved =
    savedDict->Js.Dict.get(player1Name)->Belt.Option.getWithDefault(0);
  let player2TimesSaved =
    savedDict->Js.Dict.get(player2Name)->Belt.Option.getWithDefault(0);

  savedDict->Js.Dict.set(player1Name, player1TimesSaved + 1);
  savedDict->Js.Dict.set(player2Name, player2TimesSaved + 1);

  localStorage->setItem(
    addedPlayersKey(communityName),
    Js.Json.stringifyAny(savedDict)->Belt.Option.getWithDefault(""),
  );
};

let useMostUsedPlayer = (communityName: string) => {
  let mostUsedPlayerRef =
    React.useRef(
      communityName |> getMostOftenSavedPlayerName |> Js.Nullable.fromOption,
    );

  let updateMostUsedPlayer = (player1Name, player2Name) => {
    updatePlayersAfterAddingResult(communityName, player1Name, player2Name);

    React.Ref.setCurrent(
      mostUsedPlayerRef,
      communityName |> getMostOftenSavedPlayerName |> Js.Nullable.fromOption,
    );
  };

  (mostUsedPlayerRef, updateMostUsedPlayer);
};
