open Queries;
open Utils;

module Query = [%relay.query
  {|
    query EditResultsQuery($communityName:String!, $dateFrom:timestamptz, $dateTo:timestamptz) {
      results_connection(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
        edges {
          node {
            player1 {
              id
              name
            }
            player2 {
              id
              name
            }
            player2goals
            player1goals
            extratime
            date
            id
          }
        }
      }
    }
  |}
];

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
  let dateFromString = dateFrom->Belt.Option.map(Js.Date.toISOString);
  let dateToString = dateTo->Belt.Option.map(Js.Date.toISOString);

  let queryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: dateFromString,
        dateTo: dateToString,
      },
      (),
    );
  let results = queryData.results_connection.edges |> toListOfResults5;

  <>
    <Header page={AdminResultsPage(communityName)} />
    {results->Belt.List.length === 0
       ? <MaterialUi.Card className="no-result-info">
           <MaterialUi.CardContent>
             <MaterialUi.Typography variant=`H6>
               {text("No results reported during the selected time period")}
             </MaterialUi.Typography>
           </MaterialUi.CardContent>
         </MaterialUi.Card>
       : <EditResultsTable
           communityName
           results
           //  queryToRefetch={ApolloHooks.toQueryObj(allResultsQuery)}
         />}
  </>;
};
