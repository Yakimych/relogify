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

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  React.useEffect1(
    () => {
      Js.log("useEffect");
      let lastFetchedResults =
        React.Ref.current(lastFetchedResultsRef) |> Js.Nullable.toOption;
      switch (resultsQuery) {
      | Data(data) =>
        let freshResults = data##results |> toRecord;
        switch (lastFetchedResults) {
        | Some(actualResults) =>
          let resultsToSet =
            freshResults->Belt.List.keep(r =>
              actualResults->Belt.List.has(r, (==))
            );
          Js.log2("Set new results: ", resultsToSet);
          setNewResults(_ => resultsToSet);
          ();
        | None => Js.log("Do nothing")
        };
        React.Ref.setCurrent(
          lastFetchedResultsRef,
          Js.Nullable.fromOption(Some(freshResults)),
        );
      | _ => Js.log("Do nothing")
      };
      None;
    },
    [|resultsQuery|] // TODO: This reruns forever
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
