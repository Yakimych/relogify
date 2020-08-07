open Utils;

module Query = [%relay.query
  {|
    query EditResultsQuery($communityName: String!) {
      results_connection(
        where: { community: { name: { _eq: $communityName } } }
        order_by: { date: desc }
      ) {
        ...EditResultsTable_Results
        edges {
          node {
            id
          }
        }
      }
    
      players_connection(where: { community: { name: { _eq: $communityName } } }) {
        ...PlayerPicker_Players
        ...ExistingPlayerPicker_Players
      }
    
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...AddResultTableRowFragment_CommunitySettings
            ...EditResultTableRowFragment_CommunitySettings
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName: string) => {
  let queryData = Query.use(~variables={communityName: communityName}, ());

  let communitySettingsFragment =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0).node.
      fragmentRefs;

  let playersFragment = queryData.players_connection.fragmentRefs;
  let resultsFragment = queryData.results_connection.fragmentRefs;

  <>
    <Header page={AdminResultsPage(communityName)} />
    // TODO: Move this into ResultsTable?
    {queryData.results_connection.edges->Belt.Array.length === 0
       ? <MaterialUi.Card className="no-result-info">
           <MaterialUi.CardContent>
             <MaterialUi.Typography variant=`H6>
               {text("No results reported during the selected time period")}
             </MaterialUi.Typography>
           </MaterialUi.CardContent>
         </MaterialUi.Card>
       : <EditResultsTable
           resultsFragment
           playersFragment
           communityName
           communitySettingsFragment
           //  queryToRefetch={ApolloHooks.toQueryObj(allResultsQuery)}
         />}
  </>;
};
