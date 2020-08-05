open Types;

external castToString: Js.Json.t => string = "%identity";

// TODO: DateFromString?
let dateToString = (dateString: Js.Json.t) =>
  dateString |> castToString |> Js.Date.fromString;

module AllPlayersQuery = [%graphql
  {|
    query AllPlayersQuery($communityName: String!) {
      players(where: { community: { name: { _eq: $communityName } } }) {
        id
        name
      }
    }
  |}
];

type playerWithTypeName = {
  id: int,
  name: string,
  __typename: string,
};

type resultWithTypeName = {
  player1: playerWithTypeName,
  player2: playerWithTypeName,
  player1Goals: int,
  player2Goals: int,
  extratime: bool,
  id: int,
  __typename: string,
};

type allResults = {results: array(resultWithTypeName)};
type subscriptionData = {newest_result: array(resultWithTypeName)};

external allResultsToJson: allResults => Js.Json.t = "%identity";
external toAllResults: Js.Json.t => Js.Nullable.t(allResults) = "%identity";
external toSubscriptionData: Js.Json.t => Js.Nullable.t(subscriptionData) =
  "%identity";

module CommunitySettingsQuery = [%graphql
  {|
    query communitySettings($communityName: String!) {
      community_settings(
        limit: 1
        where: { community: { name: { _eq: $communityName } } }
      ) {
        allow_draws
        max_selectable_points
        score_type
        use_dropdown_for_points
        include_extra_time
      }
    }
  |}
];

module PlayerResultsQuery = [%graphql
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
          id
          name
        }
        player1goals
        player2 {
          id
          name
        }
        player2goals
        date @bsDecoder(fn: "dateToString")
        extratime
      }
    }
  |}
];

let toListOfResults2 =
    (
      res:
        array(
          HeadToHeadPageQuery_graphql.Types.response_results_connection_edges,
        ),
    )
    : list(matchResult) =>
  res
  ->Belt.Array.map(resultNode => {
      let r = resultNode.node;
      {
        id: r.id,
        player1: {
          id: r.player1.id,
          name: r.player1.name,
        },
        player2: {
          id: r.player2.id,
          name: r.player2.name,
        },
        player1goals: r.player1goals,
        player2goals: r.player2goals,
        date: r.date |> Js.Date.fromString,
        extratime: r.extratime,
      };
    })
  ->Belt.List.fromArray;

let toListOfResults3 =
    (
      res: array(ResultsQuery_graphql.Types.response_results_connection_edges),
    )
    : list(matchResult) =>
  res
  ->Belt.Array.map(resultNode => {
      let r = resultNode.node;
      {
        id: r.id,
        player1: {
          id: r.player1.id,
          name: r.player1.name,
        },
        player2: {
          id: r.player2.id,
          name: r.player2.name,
        },
        player1goals: r.player1goals,
        player2goals: r.player2goals,
        date: r.date |> Js.Date.fromString,
        extratime: r.extratime,
      };
    })
  ->Belt.List.fromArray;

let toListOfResultsFragment =
    (res: array(ResultsTable_Results_graphql.Types.fragment_edges))
    : list(matchResult) =>
  res
  ->Belt.Array.map(resultNode => {
      let r = resultNode.node;
      {
        id: r.id,
        player1: {
          id: r.player1.id,
          name: r.player1.name,
        },
        player2: {
          id: r.player2.id,
          name: r.player2.name,
        },
        player1goals: r.player1goals,
        player2goals: r.player2goals,
        date: r.date |> Js.Date.fromString,
        extratime: r.extratime,
      };
    })
  ->Belt.List.fromArray;

let toListOfResults4 =
    (res: array(StatsQuery_graphql.Types.response_results_connection_edges))
    : list(matchResult) =>
  res
  ->Belt.Array.map(resultNode => {
      let r = resultNode.node;
      {
        id: r.id,
        player1: {
          id: r.player1.id,
          name: r.player1.name,
        },
        player2: {
          id: r.player2.id,
          name: r.player2.name,
        },
        player1goals: r.player1goals,
        player2goals: r.player2goals,
        date: r.date |> Js.Date.fromString,
        extratime: r.extratime,
      };
    })
  ->Belt.List.fromArray;

let toListOfResults5 =
    (
      res:
        array(
          EditResultsQuery_graphql.Types.response_results_connection_edges,
        ),
    )
    : list(matchResult) =>
  res
  ->Belt.Array.map(resultNode => {
      let r = resultNode.node;
      {
        id: r.id,
        player1: {
          id: r.player1.id,
          name: r.player1.name,
        },
        player2: {
          id: r.player2.id,
          name: r.player2.name,
        },
        player1goals: r.player1goals,
        player2goals: r.player2goals,
        date: r.date |> Js.Date.fromString,
        extratime: r.extratime,
      };
    })
  ->Belt.List.fromArray;

let toListOfResults = (res): list(matchResult) =>
  res
  ->Belt.Array.map(r =>
      {
        id: r##id |> string_of_int,
        player1: {
          id: r##player1##id |> string_of_int,
          name: r##player1##name,
        },
        player2: {
          id: r##player2##id |> string_of_int,
          name: r##player2##name,
        },
        player1goals: r##player1goals,
        player2goals: r##player2goals,
        date: r##date,
        extratime: r##extratime,
      }
    )
  ->Belt.List.fromArray;

let toCommunitySettingsRecord = (communitySettingsObject): communitySettings => {
  allowDraws: communitySettingsObject##allow_draws,
  maxSelectablePoints: communitySettingsObject##max_selectable_points,
  scoreType: communitySettingsObject##score_type,
  includeExtraTime: communitySettingsObject##include_extra_time,
  useDropDownForPoints: communitySettingsObject##use_dropdown_for_points,
};

let toCommunitySettings =
    (queryResult: CommunitySettingsQuery.t): communitySettings => {
  switch (queryResult##community_settings) {
  // TODO: Set default community settings in the database
  | [||] => defaultCommunitySettings
  | [|settings|] => settings |> toCommunitySettingsRecord
  | _ =>
    Js.Exn.raiseError(
      "Unexpected query result - found multiple settings for community ",
    )
  };
};
