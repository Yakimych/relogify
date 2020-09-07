open Utils;
open Types;
open EloUtils;

module ResultsTableFragment = [%relay.fragment
  {|
    fragment ResultsTable_Results on resultsConnection {
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

let toMatchResult =
    (resultNode: ResultsTableFragment.Types.fragment_edges_node): matchResult => {
  {
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
};

let dateSortFunc = (d1: Js.Date.t, d2: Js.Date.t) =>
  if (d1 < d2) {
    1;
  } else if (d1 > d2) {
    (-1);
  } else {
    0;
  };

let sortedDistinctNodeValues =
    (edges: array(ResultsTableFragment.Types.fragment_edges)) =>
  edges
  |> Array.map((e: ResultsTableFragment.Types.fragment_edges) => e.node)
  |> Array.to_list
  |> List.sort_uniq(
       (
         node1: ResultsTableFragment.Types.fragment_edges_node,
         node2: ResultsTableFragment.Types.fragment_edges_node,
       ) =>
       dateSortFunc(node1.date, node2.date)
     )
  |> Array.of_list;

[@react.component]
let make =
    (
      ~resultsTableFragment,
      ~communitySettingsFragments,
      // This can be removed as soon as ratings are persisted. Ratings will always be shown then.
      ~temp_showRatings: bool=false,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
      ~maybeDateFrom: option(Js.Date.t)=?,
    ) => {
  let lastFetchedResultIdsRef = React.useRef(Js.Nullable.null);
  let resultsTableFragment = ResultsTableFragment.use(resultsTableFragment);

  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  let sortedDistinctResults =
    resultsTableFragment.edges->sortedDistinctNodeValues;
  let resultsToDisplay =
    sortedDistinctResults->Belt.Array.keep(e =>
      maybeDateFrom->Belt.Option.mapWithDefault(true, dateFrom =>
        dateFrom <= e.date
      )
    );

  let newlyFetchedResults =
    sortedDistinctResults->Belt.Array.map(toMatchResult);

  let newResultIds =
    lastFetchedResultIdsRef.current
    ->Js.Nullable.toOption
    ->Belt.Option.mapWithDefault([||], lastFetchedResultIds =>
        resultsToDisplay
        ->Belt.Array.map(r => r.id)
        ->Belt.Array.keep(r =>
            lastFetchedResultIds
            |> Array.exists(lastResult => lastResult == r)
            |> (!)
          )
      );

  lastFetchedResultIdsRef.current =
    Js.Nullable.fromOption(
      Some(resultsToDisplay->Belt.Array.map(e => e.id)),
    );

  let resultsWithRatingMap =
    newlyFetchedResults |> Array.to_list |> attachRatings;

  resultsTableFragment.edges->Belt.Array.length === 0
    ? <MaterialUi.Card className="no-result-info">
        <MaterialUi.CardContent>
          <MaterialUi.Typography variant=`H6>
            {text("No results reported")}
          </MaterialUi.Typography>
        </MaterialUi.CardContent>
      </MaterialUi.Card>
    : <MaterialUi.Paper>
        <div className="title">
          <MaterialUi.Typography variant=`H6>
            {text("Results")}
          </MaterialUi.Typography>
        </div>
        <MaterialUi.Table size=`Small>
          <ResultsTableHeader communitySettingsFragments />
          <MaterialUi.TableBody>
            {resultsToDisplay
             ->Belt.Array.map(result => {
                 let resultWithRatings: resultWithRatings =
                   resultsWithRatingMap.resultsWithRatings
                   |> List.find(r => r.result.id === result.id);

                 <Result
                   key={result.id}
                   temp_showRatings
                   result={result.fragmentRefs}
                   resultWithRatings
                   communityName
                   mainPlayerName
                   includeExtraTimeFragments=communitySettingsFragments
                   showGraphForPlayer
                   resultIdsToHighlight={Some(newResultIds)}
                 />;
               })
             ->React.array}
          </MaterialUi.TableBody>
        </MaterialUi.Table>
        {graphIsShownForPlayer->Belt.Option.mapWithDefault(
           React.null, playerName =>
           <EloGraphDialog
             isOpen=true
             onClose=hideGraphForPlayer
             playerName
             resultsWithRatings={resultsWithRatingMap.resultsWithRatings}
           />
         )}
      </MaterialUi.Paper>;
};
