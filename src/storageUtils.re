open Dom.Storage2;

let addedPlayersKey = "added_players";

let byValue = ((_, v1), (_, v2)) => v2 - v1;

let getPlayerDict = () => {
  localStorage
  ->getItem(addedPlayersKey)
  ->Belt.Option.mapWithDefault(Js.Dict.empty(), d =>
      d |> Js.Json.parseExn |> Json.Decode.dict(Json.Decode.int)
    );
};

let getMostOftenSavedPlayerName = (): option(string) =>
  getPlayerDict()
  ->Js.Dict.entries
  ->Belt.List.fromArray
  ->Belt.List.keep(((_, v)) => v > 1)
  ->Belt.List.sort(byValue)
  ->Belt.List.map(((k, _)) => k)
  ->Belt.List.head;

let updatePlayersAfterAddingResult =
    (player1Name: string, player2Name: string) => {
  let savedDict = getPlayerDict();

  let player1TimesSaved =
    savedDict->Js.Dict.get(player1Name)->Belt.Option.getWithDefault(0);
  let player2TimesSaved =
    savedDict->Js.Dict.get(player2Name)->Belt.Option.getWithDefault(0);

  savedDict->Js.Dict.set(player1Name, player1TimesSaved + 1);
  savedDict->Js.Dict.set(player2Name, player2TimesSaved + 1);

  localStorage->setItem(
    addedPlayersKey,
    Js.Json.stringifyAny(savedDict)->Belt.Option.getWithDefault(""),
  );
};
