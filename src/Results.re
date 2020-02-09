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
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let newlyFetchedResults = data##results |> toListOfResults;
    let resultsWithRatingMap = newlyFetchedResults |> attachRatings;

    let newResultIds =
      React.Ref.current(lastFetchedResultsRef)
      ->Js.Nullable.toOption
      ->Belt.Option.mapWithDefault([], lastFetchedResults =>
          newlyFetchedResults
          ->Belt.List.keep(r => !lastFetchedResults->Belt.List.has(r, (==)))
          ->Belt.List.map(r => r.id)
        );

    React.Ref.setCurrent(
      lastFetchedResultsRef,
      Js.Nullable.fromOption(Some(newlyFetchedResults)),
    );

    newlyFetchedResults->Belt.List.length === 0
      ? <MaterialUi_Card className="no-result-info">
          <MaterialUi_CardContent>
            <Typography variant="h6">
              {React.string(
                 noResultsText->Belt.Option.getWithDefault(
                   "No results reported this week",
                 ),
               )}
            </Typography>
          </MaterialUi_CardContent>
        </MaterialUi_Card>
      : <ResultsTable
          communityName
          results={resultsWithRatingMap.resultsWithRatings}
          resultIdsToHighlight={highlightNewResults ? newResultIds : []}
          temp_showRatings
        />;
  };
};
