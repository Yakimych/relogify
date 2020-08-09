module Query = [%relay.query
  {|
    query CommunityAdminPageQuery($communityName: String!) {
      results_connection(
        first: 1000
        where: { community: { name: { _eq: $communityName } } }
        order_by: { date: desc }
      ) @connection(key: "EditResults_query_results_connection", filters: []) {
        ...EditResultsFragment
        edges {
          node {
            id
          }
        }
      }

      players_connection(
        first: 1000
        where: { community: { name: { _eq: $communityName } } }
      ) @connection(key: "EditResults_query_players_connection", filters: []) {
        ...PlayerPicker_Players
        ...ExistingPlayerPicker_Players
        edges {
          node {
            id
          }
        }
      }

      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...AddResultTableRowFragment_CommunitySettings
            ...EditResultTableRowFragment_CommunitySettings
            ...EditSettingsFragment_CommunitySettings
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName, ~subRoute) => {
  let queryData = Query.use(~variables={communityName: communityName}, ());

  let playersFragment = queryData.players_connection.fragmentRefs;
  let resultsFragment = queryData.results_connection.fragmentRefs;

  let communitySettingsFragment =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0).node.
      fragmentRefs;

  switch (subRoute) {
  | ["settings"] =>
    <EditSettings
      communityName
      editSettingsFragment=communitySettingsFragment
    />
  | ["players"] => <EditPlayers communityName />
  | ["results"]
  | _ =>
    <EditResults
      communityName
      editResultsFragment=resultsFragment
      playersFragment
      communitySettingsFragment
    />
  };
};
