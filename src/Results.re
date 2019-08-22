open Queries;
open Utils;
open Types;

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~highlightNewResults: bool,
    ) => {
  // lastFetchedResultsRef
  let newResults = [||];

  let allResultsQuery =
    AllResultsQueryConfig.make(
      ~communityName,
      ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
      ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
      (),
    );

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    <ResultsTable
      communityName
      results={data##results |> toRecord}
      newResults={highlightNewResults ? newResults : [||]}
    />
  };
};
