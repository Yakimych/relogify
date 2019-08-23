open Queries;
open Utils;

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

      switch (resultsQuery) {
      | Data(data) =>
        let freshResults = data##results |> toRecord;
        switch (lastFetchedResults) {
        | Some(actualLastFetchedResults) =>
          setNewResults(_ =>
            freshResults->Belt.List.keep(r =>
              !actualLastFetchedResults->Belt.List.has(r, (==))
            )
          )
        | None => ()
        };

        React.Ref.setCurrent(
          lastFetchedResultsRef,
          Js.Nullable.fromOption(Some(freshResults)),
        );
      | _ => ()
      };
      None;
    },
    [|
      fullResultsQuery.data
      ->Belt.Option.map(d => d##results->Belt.Array.length),
    |],
  );

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    <ResultsTable
      communityName
      results={data##results |> toRecord}
      newResults={highlightNewResults ? newResults : []}
    />
  };
};
