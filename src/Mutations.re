module AddResultMutationConfig = [%graphql
  {|
  mutation AddResultMutation(
    $communityName: String!
    $player1Name: String!
    $player2Name: String!
    $date: timestamptz!
    $player1Goals: Int!
    $player2Goals: Int!
    $extraTime: Boolean!
  ) {
    insert_results(
      objects: {
        community: {
          data: { name: $communityName }
          on_conflict: {
            constraint: communities_name_key
            update_columns: name
          }
        }
        date: $date
        player1: {
          data: {
            name: $player1Name
            community: {
              data: { name: $communityName }
              on_conflict: {
                constraint: communities_name_key
                update_columns: name
              }
            }
          }
          on_conflict: {
            constraint: players_name_communityId_key
            update_columns: name
          }
        }
        player2: {
          data: {
            name: $player2Name
            community: {
              data: { name: $communityName }
              on_conflict: {
                constraint: communities_name_key
                update_columns: name
              }
            }
          }
          on_conflict: {
            constraint: players_name_communityId_key
            update_columns: name
          }
        }
        player2goals: $player2Goals
        player1goals: $player1Goals
        extratime: $extraTime
      }
    ) {
      returning {
        id
      }
    }
  }
|}
];

module AddResultMutation =
  ReasonApolloHooks.Mutation.Make(AddResultMutationConfig);

module UpdateResultMutationConfig = [%graphql
  {|
    mutation UpdateResultMutation(
      $resultId: Int!
      $player1Id: Int!
      $player2Id: Int!
      $player1Goals: Int!
      $player2Goals: Int!
      $extraTime: Boolean!
    ) {
      update_results(
        where: {
          id: {
            _eq: $resultId
          }
        }
        _set: {
          player1Id: $player1Id
          player1goals: $player1Goals
          player2goals: $player2Goals
          player2Id: $player2Id
          extratime: $extraTime
        }
      ) {
        affected_rows
      }
    }
  |}
];

module UpdateResultMutation =
  ReasonApolloHooks.Mutation.Make(UpdateResultMutationConfig);
