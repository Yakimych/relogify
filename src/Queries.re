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
        date
        id
      }
    }
  |}
];

module AllResultsQuery = ReasonApolloHooks.Query.Make(AllResultsQueryConfig);
