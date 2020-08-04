open Utils;
open Types;
open EloUtils;

module Query = [%relay.query
  {|
    query ResultsTableQuery(
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
        edges {
          node {
            ...Result_SingleResult
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
            ...ExtraTimeColumn_IncludeExtraTime
            ...ResultsTableHeader_CommunitySettings
          }
        }
      }
    }
  |}
];

let getHighlightedClassName =
    (newResults: option(list(string)), currentResult: matchResult) => {
  let resultIsFresh =
    newResults
    ->Belt.Option.map(n => n->Belt.List.some(id => id == currentResult.id))
    ->Belt.Option.getWithDefault(false);

  resultIsFresh ? "highlighted" : "";
};

let getWinningLosingRowClassName = (mainPlayerWon: bool) =>
  mainPlayerWon ? "winning-row" : "";

[@react.component]
let make =
    (
      ~results: list(resultWithRatings),
      // This can be removed as soon as ratings are persisted. Ratings will always be shown then.
      ~temp_showRatings: bool=false,
      // TODO: Implement highlighting
      ~resultIdsToHighlight: option(list(string))=?,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
  // TODO: Remove the query from the parent or more the query higher up and pass the fragments down instead?
  let localResultsQueryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: dateFrom->Belt.Option.map(Js.Date.toISOString),
        dateTo: dateTo->Belt.Option.map(Js.Date.toISOString),
      },
      (),
    );

  let communitySettingsFragment =
    localResultsQueryData.community_settings_connection.edges
    ->Belt.Array.getExn(0).
      node.
      fragmentRefs;

  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  <MaterialUi.Paper>
    <div className="title">
      <MaterialUi.Typography variant=`H6>
        {text("Results")}
      </MaterialUi.Typography>
    </div>
    <MaterialUi.Table size=`Small>
      <ResultsTableHeader communitySettingsFragment />
      <MaterialUi.TableBody>
        {localResultsQueryData.results_connection.edges
         ->Belt.Array.map(localResult => {
             let resultWithRatings: resultWithRatings =
               results |> List.find(r => r.result.id === localResult.node.id);

             <Result
               temp_showRatings
               result={localResult.node.fragmentRefs}
               resultWithRatings
               communityName
               mainPlayerName
               includeExtraTimeFragment=communitySettingsFragment
               showGraphForPlayer
             />;
           })
         ->React.array}
      </MaterialUi.TableBody>
    </MaterialUi.Table>
    {graphIsShownForPlayer->Belt.Option.mapWithDefault(React.null, playerName =>
       <EloGraphDialog
         isOpen=true
         onClose=hideGraphForPlayer
         playerName
         resultsWithRatings=results
       />
     )}
  </MaterialUi.Paper>;
};
