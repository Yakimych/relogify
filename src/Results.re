open Queries;
open Utils;
open EloUtils;
open ApolloHooks;

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

  let (resultsQuery, _) =
    useQuery(
      ~variables=
        AllResultsQuery.makeVariables(
          ~communityName,
          ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
          ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
          (),
        ),
      AllResultsQuery.definition,
    );

  switch (resultsQuery) {
  | Loading => <MaterialUi.CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let newlyFetchedResults = data##results |> toListOfResults;
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
};
