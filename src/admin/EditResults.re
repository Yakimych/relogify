open Queries;
open Utils;
open ApolloHooks;

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
  let allResultsQuery =
    AllResultsQuery.make(
      ~communityName,
      ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
      ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
      (),
    );

  let (resultsQuery, _) =
    useQuery(
      ~variables=allResultsQuery##variables,
      AllResultsQuery.definition,
    );

  <>
    <Header page={AdminResultsPage(communityName)} />
    {switch (resultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let results = data##results |> toListOfResults;

       results->Belt.List.length === 0
         ? <MaterialUi_Card className="no-result-info">
             <CardContent>
               <Typography variant="h6">
                 {React.string(
                    "No results reported during the selected time period",
                  )}
               </Typography>
             </CardContent>
           </MaterialUi_Card>
         : <EditResultsTable
             communityName
             results
             queryToRefetch={ApolloHooks.toQueryObj(allResultsQuery)}
           />;
     }}
  </>;
};
