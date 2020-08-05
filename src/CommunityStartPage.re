open Utils;

// TODO: Spread the fragments inside results_connection and pass down
module Query = [%relay.query
  {|
    query CommunityStartPageQuery(
      $communityName: String!
      $dateFrom: timestamptz
      $dateTo: timestamptz
    ) {
      results_connection(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
        ...ResultsTable_Results
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
            ...ExtraTimeColumn_IncludeExtraTime
            ...ResultsTableHeader_CommunitySettings
            ...AddResultFragment_CommunitySettings
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName) => {
  let (startDate, endDate) = getCurrentWeek();

  let queryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: Some(startDate |> Js.Date.toISOString),
        dateTo: Some(endDate |> Js.Date.toISOString),
      },
      (),
    );

  let resultsTableFragment = queryData.results_connection.fragmentRefs;

  let communitySettingsFragment =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0).node.
      fragmentRefs;

  <>
    <CommunityStartPageHeader communityName communitySettingsFragment />
    <Stats communityName dateFrom=startDate dateTo=endDate />
    <ResultsTable
      resultsTableFragment
      communitySettingsFragment
      communityName
      dateFrom=startDate
      dateTo=endDate
      // highlightNewResults=true
    />
  </>;
};
