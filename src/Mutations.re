module AddResultMutation = [%graphql
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
    mutation DeleteResultMutation(
      $resultId: Int!
    ) {
      delete_results(
        where: {
          id: {
            _eq: $resultId
          }
        }
      ) {
        affected_rows
      }
    }
  |}
];

module UpdateCommunitySettingsMutation = [%graphql
  {|
    mutation updateCommunitySettingsMutation(
      $communityName: String!,
      $allowDraws: Boolean,
      $maxSelectablePoints: Int,
      $scoreType: score_types_enum,
      $includeExtraTime: Boolean,
      $useDropDownForPoints: Boolean,
    ) {
      update_community_settings(
        where: {
          community: {
            name: {
                _eq: $communityName
              }
            }
          },
        _set: {
          allow_draws: $allowDraws,
          max_selectable_points: $maxSelectablePoints,
          score_type: $scoreType,
          include_extra_time: $includeExtraTime,
          use_dropdown_for_points: $useDropDownForPoints,
        }
      ) {
        affected_rows
      }
    }
  |}
];

module CreateCommunitySettingsMutation = [%graphql
  {|
    mutation createCommunitySettingsMutation(
      $communityName: String!,
      $allowDraws: Boolean,
      $maxSelectablePoints: Int,
      $scoreType: score_types_enum,
      $includeExtraTime: Boolean,
      $useDropDownForPoints: Boolean,
    ) {
        insert_community_settings(
          objects: {
            community: {
              data: {
                name: $communityName
              },
              on_conflict: {
                constraint: communities_name_key,
                update_columns: name
              }
            },
            include_extra_time: $includeExtraTime,
            max_selectable_points: $maxSelectablePoints,
            score_type: $scoreType,
            use_dropdown_for_points: $useDropDownForPoints,
            allow_draws: $allowDraws}
         ) {
            affected_rows
           }
      }
  |}
];
