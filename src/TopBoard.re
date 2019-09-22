open DateFns;
open Utils;
open EloUtils;
open Queries;
open Subscriptions;

let topNumberOfRows = 5;

[@react.component]
let make = (~communityName: string) => {
  let now = Js.Date.make();
  let startOfDay = now->startOfDay;
  let weekStartDate = now->startOfWeek({"weekStartsOn": 1});
  let monthStartDate = now->startOfMonth;
  let yearStartDate = now->startOfYear;

  let allResultsQuery = AllResultsQueryConfig.make(~communityName, ());

  let (resultsQuery, fullResultsQuery) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  let newResultSubscription =
    NewResultSubscriptionConfig.make(~communityName, ());
  let newResultDocument = ApolloClient.gql(. newResultSubscription##query);
  let newResultsRef = React.useRef([]);

  React.useEffect1(
    () => {
      fullResultsQuery.subscribeToMore(
        ~document=newResultDocument,
        ~variables=newResultSubscription##variables,
        ~updateQuery=[%bs.raw
          {|
            function(prev, { subscriptionData }) {
              const newestResult = subscriptionData.data.newest_result[0];
              const alreadyInList =
                newestResult && prev.results.filter(r => r.id === newestResult.id)[0];
              const resultsToAdd = alreadyInList ? [] : [newestResult];
              newResultsRef.current = resultsToAdd.map(r => r.id);
              return {
                results: [...resultsToAdd, ...prev.results]
              };
            }
          |}
        ],
        (),
      )
      |> ignore;
      None;
    },
    [|communityName|],
  );

  Js.log2("Ref: ", React.Ref.current(newResultsRef));

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let results = data##results |> toRecord;
    let resultsWithRatingMap = results |> attachRatings;

    <>
      <Header page={TopX(communityName)} />
      <Box margin="10px" textAlign="center">
        // <Stats
        //   communityName
        //   dateFrom=yearStartDate
        //   dateTo=now
        //   playerLimit=topNumberOfRows
        //   title="This year"
        // />

          <ResultsTable
            communityName
            results={resultsWithRatingMap.resultsWithRatings}
            // TODO
            // newResults={highlightNewResults ? newResults : []}
            newResultIds={React.Ref.current(newResultsRef)}
            temp_showRatings=true
          />
        </Box>
    </>;
  };
};
