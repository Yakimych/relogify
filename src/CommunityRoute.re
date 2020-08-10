open Utils;

module Query = [%relay.query
  {|
    query CommunityRouteQuery(
      $communityName: String!
      $dateFrom: timestamptz
      $dateTo: timestamptz
    ) {
      results_connection(
        first: 1000
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) @connection(key: "CommunityRoute_query_results_connection", filters: []) {
        ...ResultsTable_Results
        ...Stats_Results
        edges {
          node {
            id
          }
        }
      }

      players_connection(
        first: 1000
        where: { community: { name: { _eq: $communityName } } }
      ) @connection(key: "CommunityRoute_query_players_connection", filters: []) {
        ...PlayerPicker_Players
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
            ...StatsTableHeader_ScoreType
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName, ~subRoute) => {
  // TODO: Start and end dates should depend on the route
  let (startDate, endDate) = getCurrentWeek();

  let queryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: Some(startDate),
        dateTo: Some(endDate),
      },
      (),
    );

  let resultsFragment = queryData.results_connection.fragmentRefs;

  let communitySettingsFragment =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0).node.
      fragmentRefs;

  let playersFragment = queryData.players_connection.fragmentRefs;

  switch (subRoute) {
  | [] =>
    <MaterialUi.Container maxWidth=`Sm>
      <CommunityStartPage
        communityName
        resultsFragment
        communitySettingsFragment
        playersFragment
      />
    </MaterialUi.Container>
  // TODO: Extract TopBoard to top level, since it is going to be subscription-based anyway?
  | ["top"] =>
    <MaterialUi.Container maxWidth=`Lg>
      <div> {text("PLACEHOLDER FOR TOPBOARD: " ++ communityName)} </div>
    </MaterialUi.Container>
  // <TopBoard communityName />
  // TODO: Parametrize the history route
  // | ["history", startYear, startMonth, startDay, endYear, endMonth, endDay] =>
  | ["history"] =>
    <MaterialUi.Container maxWidth=`Sm>
      <ResultHistory communityName resultsFragment communitySettingsFragment />
    </MaterialUi.Container>
  | [playerName] =>
    <MaterialUi.Container maxWidth=`Sm>
      <PlayerResults communityName playerName />
    </MaterialUi.Container>
  | [player1Name, player2Name] =>
    <MaterialUi.Container maxWidth=`Sm>
      <HeadToHeadPage communityName player1Name player2Name />
    </MaterialUi.Container>
  | _ =>
    <MaterialUi.Container maxWidth=`Sm>
      <div> {text("Invalid route")} </div>
    </MaterialUi.Container>
  };
};
