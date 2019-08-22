external castToString: Js.Json.t => string = "%identity";

let dateToString = (dateString: Js.Json.t) =>
  dateString |> castToString |> Js.Date.fromString;

module AllPlayersQueryConfig = [%graphql
  {|
  query AllPlayersQuery($communityName: String!) {
    players(where: { community: { name: { _eq: $communityName } } }) {
      id
      name
    }
  }
|}
];

module AllPlayersQuery = ReasonApolloHooks.Query.Make(AllPlayersQueryConfig);

module AllResultsQueryConfig = [%graphql
  {|
  query AllResultsQuery($communityName: String!, $dateFrom: timestamptz, $dateTo: timestamptz) {
      results(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
        player1 {
          name
        }
        player2 {
          name
        }
        player2goals
        player1goals
        extratime
        date @bsDecoder (fn: "dateToString")
        id
      }
    }
  |}
];

module AllResultsQuery = ReasonApolloHooks.Query.Make(AllResultsQueryConfig);

module HeadToHeadQueryConfig = [%graphql
  {|
  query($communityName: String!, $player1Name: String!, $player2Name: String!) {
    results(
      where: {
        _and: [
          { community: { name: { _eq: $communityName } } }
          {
            _or: [
              { player1: { name: { _eq: $player1Name } } }
              { player2: { name: { _eq: $player1Name } } }
            ]
          }
          {
            _or: [
              { player1: { name: { _eq: $player2Name } } }
              { player2: { name: { _eq: $player2Name } } }
            ]
          }
        ]
      }
      order_by: { date: desc }
    ) {
      id
      player1 {
        name
      }
      player1goals
      player2 {
        name
      }
      player2goals
      date @bsDecoder (fn: "dateToString")
      extratime
    }
  }
|}
];

module HeadToHeadQuery = ReasonApolloHooks.Query.Make(HeadToHeadQueryConfig);

module PlayerResultsQueryConfig = [%graphql
  {|
  query playerResults($communityName: String!, $playerName: String!) {
    results(
      where: {
        _and: [
          { community: { name: { _eq: $communityName } } }
          {
            _or: [
              { player1: { name: { _eq: $playerName } } }
              { player2: { name: { _eq: $playerName } } }
            ]
          }
        ]
      }
      order_by: { date: desc }
    ) {
      id
      player1 {
        name
      }
      player1goals
      player2 {
        name
      }
      player2goals
      date @bsDecoder (fn: "dateToString")
      extratime
    }
  }
|}
];

module PlayerResultsQuery =
  ReasonApolloHooks.Query.Make(PlayerResultsQueryConfig);

/* TODO: bsRecord instead of a mapping function */
open Types;
let toRecord = (res): array(result) =>
  res->Belt.Array.map(r =>
    {
      id: r##id,
      player1: {
        name: r##player1##name,
      },
      player2: {
        name: r##player2##name,
      },
      player1goals: r##player1goals,
      player2goals: r##player2goals,
      date: r##date,
      extratime: r##extratime,
    }
  );