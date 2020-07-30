open Queries;
open Utils;
open EloUtils;

module Query = [%relay.query
  {|
    query ResultsQuery($communityName:String!, $dateFrom:timestamptz, $dateTo:timestamptz) {
      results_connection(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
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

[@react.component]
let make =
    (
      ~communityName: string,
      ~temp_showRatings: bool=false,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~highlightNewResults: bool,
      ~noResultsText: option(string)=?,
    ) => {
  let lastFetchedResultsRef = React.useRef(Js.Nullable.null);

  let dateFromString = dateFrom->Belt.Option.map(Js.Date.toISOString);
  let dateToString = dateTo->Belt.Option.map(Js.Date.toISOString);

  let queryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: dateFromString,
        dateTo: dateToString,
      },
      (),
    );

  let newlyFetchedResults =
    queryData.results_connection.edges |> toListOfResults3;
  let resultsWithRatingMap = newlyFetchedResults |> attachRatings;

  let newResultIds =
    lastFetchedResultsRef.current
    ->Js.Nullable.toOption
    ->Belt.Option.mapWithDefault([], lastFetchedResults =>
        newlyFetchedResults
        ->Belt.List.keep(r => !lastFetchedResults->Belt.List.has(r, (==)))
        ->Belt.List.map(r => r.id)
      );

  lastFetchedResultsRef.current =
    Js.Nullable.fromOption(Some(newlyFetchedResults));

  newlyFetchedResults->Belt.List.length === 0
    ? <MaterialUi.Card className="no-result-info">
        <MaterialUi.CardContent>
          <MaterialUi.Typography variant=`H6>
            {text(
               noResultsText->Belt.Option.getWithDefault(
                 "No results reported this week",
               ),
             )}
          </MaterialUi.Typography>
        </MaterialUi.CardContent>
      </MaterialUi.Card>
    : <ResultsTable
        communityName
        results={resultsWithRatingMap.resultsWithRatings}
        resultIdsToHighlight={highlightNewResults ? newResultIds : []}
        temp_showRatings
      />;
};
