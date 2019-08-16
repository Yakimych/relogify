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

  <ResultsTable
    communityName
    results=[||]
    newResults={highlightNewResults ? newResults : [||]}
  />;
};
