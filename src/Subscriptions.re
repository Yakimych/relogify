module NewResultSubscription = [%graphql
  {|
    subscription newResult($communityName: String!) {
      newest_result(where: { community: { name: { _eq: $communityName } } }) {
        player1 {
          id
          name
        }
        player2 {
          id
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
