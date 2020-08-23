open DateFns;
open EloUtils;

module TopBoardQuery = [%relay.query
  {|
    query TopBoardQuery($communityName: String!) {
      results_connection(
        first: 1000
        where: { community: { name: { _eq: $communityName } } }
        order_by: { date: desc }
      ) @connection(key: "TopBoard_query_results_connection", filters: []) {
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

module TopBoardSubscription = [%relay.subscription
  {|
    subscription TopBoardSubscription($communityName: String!) {
      results_connection(
        first: 1
        order_by: { date: desc }
        where: { community: { name: { _eq: $communityName } } }
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
    }
  |}
];

let toMatchResult =
    (resultNode: TopBoardQuery.Types.response_results_connection_edges_node)
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

let distinctNodeValues =
    (edges: array(TopBoardQuery.Types.response_results_connection_edges)) =>
  edges
  ->Belt.Array.map(e => (e.node.id, e.node))
  ->Belt_MapString.fromArray
  ->Belt_MapString.toArray
  ->Belt.Array.map(((_, value)) => value);

[@react.component]
let make = (~communityName: string) => {
  let now = Js.Date.make();
  let startOfDay = now->startOfDay;

  let weekStartDate =
    now->DateFns.startOfWeekOpt({locale: None, weekStartsOn: Some(1)});
  let monthStartDate = now->startOfMonth;
  let yearStartDate = now->startOfYear;

  let queryData =
    TopBoardQuery.use(~variables={communityName: communityName}, ());
  let resultsFragment = queryData.results_connection.fragmentRefs;

  let results =
    queryData.results_connection.edges
    ->distinctNodeValues
    ->Belt.Array.map(e => e->toMatchResult)
    ->Belt.List.fromArray;

  let resultsWithRatingMap = results |> attachRatings;

  let communitySettingsFragments =
    queryData.community_settings_connection.edges
    ->Belt.Array.map(e => e.node.fragmentRefs);

  let environment = ReasonRelay.useEnvironmentFromContext();
  React.useEffect1(
    () => {
      let subscription =
        TopBoardSubscription.subscribe(
          ~environment,
          ~variables={communityName: communityName},
          ~updater=
            (
              store: ReasonRelay.RecordSourceSelectorProxy.t,
              response: TopBoardSubscription.Types.response,
            ) => {
              switch (response.results_connection.edges) {
              | [|newest_result|] =>
                StoreUpdater.updateResultList(
                  store,
                  newest_result.node.id,
                  "TopBoard_query_results_connection",
                )
              | _ => Js.log("Expected exactly 1 result (0 or >1 received)")
              }
            },
          (),
        );
      Some(() => ReasonRelay.Disposable.dispose(subscription));
    },
    [|communityName|],
  );

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
