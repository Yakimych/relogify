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
    (resultNode: ResultsTable_Results_graphql.Types.fragment_edges_node)
    : matchResult => {
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

[@react.component]
let make =
    (
      ~resultsTableFragment,
      ~communitySettingsFragment,
      // This can be removed as soon as ratings are persisted. Ratings will always be shown then.
      ~temp_showRatings: bool=false,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
    ) => {
  let lastFetchedResultIdsRef = React.useRef(Js.Nullable.null);
  let resultsTableFragment = ResultsTableFragment.use(resultsTableFragment);

  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  let newlyFetchedResults =
    resultsTableFragment.edges->Belt.Array.map(e => e.node->toMatchResult);

  let newResultIds =
    lastFetchedResultIdsRef.current
    ->Js.Nullable.toOption
    ->Belt.Option.mapWithDefault([||], lastFetchedResultIds =>
        resultsTableFragment.edges
        ->Belt.Array.map(r => r.node.id)
        ->Belt.Array.keep(r =>
            lastFetchedResultIds
            |> Array.exists(lastResult => lastResult == r)
            |> (!)
          )
      );

  lastFetchedResultIdsRef.current =
    Js.Nullable.fromOption(
      Some(resultsTableFragment.edges->Belt.Array.map(e => e.node.id)),
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
          <ResultsTableHeader communitySettingsFragment />
          <MaterialUi.TableBody>
            {resultsTableFragment.edges
             ->Belt.Array.map(result => {
                 let resultWithRatings: resultWithRatings =
                   resultsWithRatingMap.resultsWithRatings
                   |> List.find(r => r.result.id === result.node.id);

                 <Result
                   key={result.node.id}
                   temp_showRatings
                   result={result.node.fragmentRefs}
                   resultWithRatings
                   communityName
                   mainPlayerName
                   includeExtraTimeFragment=communitySettingsFragment
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
