open Queries;
open Utils;

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
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
    let results = data##results |> toRecord;

    results->Belt.List.length === 0
      ? <Card className="no-result-info">
          <CardContent>
            <Typography variant="h6">
              {React.string(
                 "No results reported during the selected time period",
               )}
            </Typography>
          </CardContent>
        </Card>
      : <EditResultsTable
          communityName
          results
          queryToRefetch={ReasonApolloHooks.Utils.toQueryObj(allResultsQuery)}
        />;
  };
};
