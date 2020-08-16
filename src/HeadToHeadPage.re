open Utils;
open PlayerStatsUtils;
open Types;

module Query = [%relay.query
  {|
    query HeadToHeadPageQuery(
      $communityName: String!
      $player1Name: String!
      $player2Name: String!
    ) {
      results_connection(
        where: {
          _and: [
            { community: { name: { _eq: $communityName } } }
            {
              _or: [
                { player1: { name: { _eq: $player1Name } } }
                { player2: { name: { _eq: $player1Name } } }
              ]
            }
            {
              _or: [
                { player1: { name: { _eq: $player2Name } } }
                { player2: { name: { _eq: $player2Name } } }
              ]
            }
          ]
        }
        order_by: { date: desc }
      ) {
        ...ResultsTable_Results
        edges {
          node {
            id
            player1 {
              id
              name
            }
            player1goals
            player2 {
              id
              name
            }
            player2goals
            date
            extratime
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
          }
        }
      }
    }
  |}
];

let toMatchResult =
    (
      resultNode: HeadToHeadPageQuery_graphql.Types.response_results_connection_edges_node,
    )
    : matchResult => {
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
let make = (~communityName, ~player1Name, ~player2Name) => {
  let queryData =
    Query.use(~variables={communityName, player1Name, player2Name}, ());

  let matchResults =
    queryData.results_connection.edges
    ->Belt.Array.map(e => e.node->toMatchResult)
    ->Belt.List.fromArray;

  let stats = getPlayerStats(player1Name, matchResults);

  let resultsTableFragment = queryData.results_connection.fragmentRefs;

  let maybeCommunitySettingsFragment =
    queryData.community_settings_connection.edges
    ->Belt.Array.get(0)
    ->Belt.Option.map(e => e.node.fragmentRefs);

  <>
    <Header page={HeadToHead(communityName, player1Name, player2Name)} />
    <>
      <MaterialUi.Box textAlign="center">
        <MaterialUi.Typography variant=`H4>
          {text(player1Name ++ " vs " ++ player2Name)}
        </MaterialUi.Typography>
        <div>
          <span className="stats-player-goals">
            {text("(" ++ string_of_int(stats.goalsScored) ++ ")")}
          </span>
          {text(" ")}
          <span className="stats-player-wins">
            {text(
               string_of_int(stats.matchesWon)
               ++ " - "
               ++ string_of_int(stats.matchesLost),
             )}
          </span>
          {text(" ")}
          <span className="stats-player-goals">
            {text("(" ++ string_of_int(stats.goalsConceded) ++ ")")}
          </span>
        </div>
      </MaterialUi.Box>
      <ReactMinimalPieChart
        data=[|
          {
            "title": player1Name,
            "value": stats.matchesWon,
            "color": "#00cc00",
          },
          {
            "title": player2Name,
            "value": stats.matchesLost,
            "color": "#ff2200",
          },
        |]
        style={ReactDOMRe.Style.make(
          ~height="100px",
          ~marginBottom="10px",
          (),
        )}
        animate=true
        lineWidth=80
        label=true
        labelStyle={ReactDOMRe.Style.make(
          ~fontSize="20px",
          ~fill="#ffffff",
          (),
        )}
      />
      <ResultsTable
        resultsTableFragment
        maybeCommunitySettingsFragment
        communityName
      />
    </>
  </>;
};
