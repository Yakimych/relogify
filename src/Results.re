open Queries;
open Utils;
open EloUtils;

[@react.component]
let make =
    (
      ~communityName: string,
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
    [|
      fullResultsQuery.data
      // TODO: remove this line when
      // https://github.com/Yakimych/reason-apollo-hooks/tree/memoize-result-in-query is merged
      ->Belt.Option.map(d => d##results->Belt.Array.length),
    |],
  );

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let results = data##results |> toRecord;
    let state = results |> attachRatings;

    <ResultsTable
      communityName
      results={state.resultsWithRatings}
      newResults={highlightNewResults ? newResults : []}
    />;
  };
};
