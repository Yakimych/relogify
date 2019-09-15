open Queries;
open Utils;
open EloUtils;

[@react.component]
let make =
    (
      ~communityName: string,
      ~temp_showRatings: bool=false,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~highlightNewResults: bool,
    ) => {
  let lastFetchedResultsRef = React.useRef(Js.Nullable.null);
  let (newResults, setNewResults) = React.useState(_ => []);

  let allResultsQuery =
    AllResultsQueryConfig.make(
      ~communityName,
      ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
      ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
      (),
    );

  let (resultsQuery, fullResultsQuery) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  React.useEffect1(
    () => {
      let lastFetchedResults =
        React.Ref.current(lastFetchedResultsRef) |> Js.Nullable.toOption;

      fullResultsQuery.data
      ->Belt.Option.map(data => {
          let newlyFetchedResults = data##results |> toRecord;
          lastFetchedResults->Belt.Option.map(ar =>
            setNewResults(_ =>
              newlyFetchedResults->Belt.List.keep(r =>
                !ar->Belt.List.has(r, (==))
              )
            )
          )
          |> ignore;

          React.Ref.setCurrent(
            lastFetchedResultsRef,
            Js.Nullable.fromOption(Some(newlyFetchedResults)),
          );
        })
      |> ignore;
      None;
    },
    [|fullResultsQuery.data|],
  );

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let results = data##results |> toRecord;
    let resultsWithRatingMap = results |> attachRatings;

    results->Belt.List.length === 0
      ? <Card className="no-result-info">
          <CardContent>
            <Typography variant="h6">
              {React.string("No results reported this week")}
            </Typography>
          </CardContent>
        </Card>
      : <ResultsTable
          communityName
          results={resultsWithRatingMap.resultsWithRatings}
          newResults={highlightNewResults ? newResults : []}
          temp_showRatings
        />;
  };
};
