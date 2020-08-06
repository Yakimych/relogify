module UpdateResultMutation = [%graphql
  {|
    mutation UpdateResultMutation(
      $resultId: Int!
      $player1Id: Int!
      $player2Id: Int!
      $player1Goals: Int!
      $player2Goals: Int!
      $extraTime: Boolean!
      $date: timestamptz!
    ) {
      update_results(
        where: { id: { _eq: $resultId } }
        _set: {
          player1Id: $player1Id
          player1goals: $player1Goals
          player2goals: $player2Goals
          player2Id: $player2Id
          extratime: $extraTime
          date: $date
        }
      ) {
        affected_rows
      }
    }
  |}
];

module DeleteResultMutation = [%graphql
  {|
    mutation DeleteResultMutation($resultId: Int!) {
      delete_results(where: { id: { _eq: $resultId } }) {
        affected_rows
      }
    }
  |}
];
