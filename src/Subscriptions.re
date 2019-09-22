module NewResultSubscriptionConfig = [%graphql
  {|
    subscription newResult($communityName: String!) {
      newest_result(where: { community: { name: { _eq: $communityName } } }) {
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

module NewResultSubscription =
  ReasonApolloHooks.Subscription.Make(NewResultSubscriptionConfig);
