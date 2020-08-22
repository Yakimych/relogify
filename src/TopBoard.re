open DateFns;
open EloUtils;

module Query = [%relay.query
  {|
    query TopBoardQuery($communityName: String!) {
      results_connection(
        where: { community: { name: { _eq: $communityName } } }
        order_by: { date: desc }
      ) {
        ...ResultsTable_Results
        edges {
          node {
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
      }
    
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...ResultCommunitySettings_IncludeExtraTime
            ...ResultsTableHeader_CommunitySettings
            ...TopStatsColumn_ScoreType
          }
        }
      }
    }
  |}
];

let toMatchResult =
    (
      resultNode: TopBoardQuery_graphql.Types.response_results_connection_edges_node,
    )
    : Types.matchResult => {
  id: resultNode.id,
  player1: {
    id: resultNode.player1.id,
    name: resultNode.player1.name,
  },
  player2: {
    id: resultNode.player2.id,
    name: resultNode.player2.name,
  },
  player1goals: resultNode.player1goals,
  player2goals: resultNode.player2goals,
  date: resultNode.date,
  extratime: resultNode.extratime,
};

[@react.component]
let make = (~communityName: string) => {
  let now = Js.Date.make();
  let startOfDay = now->startOfDay;

  let weekStartDate =
    now->DateFns.startOfWeekOpt({locale: None, weekStartsOn: Some(1)});
  let monthStartDate = now->startOfMonth;
  let yearStartDate = now->startOfYear;

  let queryData = Query.use(~variables={communityName: communityName}, ());
  let resultsFragment = queryData.results_connection.fragmentRefs;

  let results =
    queryData.results_connection.edges
    ->Belt.Array.map(e => e.node->toMatchResult)
    ->Belt.List.fromArray;

  let resultsWithRatingMap = results |> attachRatings;

  let communitySettingsFragments =
    queryData.community_settings_connection.edges
    ->Belt.Array.map(e => e.node.fragmentRefs);

  <>
    <Header page={TopX(communityName)} />
    <MaterialUi.Box margin="10px" textAlign="center">
      <TopStats
        scoreTypeFragment=communitySettingsFragments
        title="This Week"
        resultsWithMap=resultsWithRatingMap
        startDate=weekStartDate
      />
      <TopStats
        scoreTypeFragment=communitySettingsFragments
        title="This Month"
        resultsWithMap=resultsWithRatingMap
        startDate=monthStartDate
      />
      <TopStats
        scoreTypeFragment=communitySettingsFragments
        title="This Year"
        resultsWithMap=resultsWithRatingMap
        startDate=yearStartDate
      />
      {resultsWithRatingMap.resultsWithRatings
       |> List.exists(r => r.result.date >= startOfDay)
         ? <ResultsTable
             communityName
             resultsTableFragment=resultsFragment
             communitySettingsFragments
             temp_showRatings=true
             maybeDateFrom=startOfDay
           />
         : React.null}
    </MaterialUi.Box>
  </>;
};
