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
  let newResultRef = React.useRef(None);

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
              newResultRef.current = alreadyInList ? undefined : newestResult.id;
              return {
                results: [...(alreadyInList ? [] : [newestResult]), ...prev.results]
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

  switch (resultsQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let results = data##results |> toRecord;
    let resultsWithRatingMap = results |> attachRatings;

    let resultIdsToHighlight =
      React.Ref.current(newResultRef)
      ->Belt.Option.mapWithDefault([], v => [v]);

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

          <TopStats title="This Week" />
          <ResultsTable
            communityName
            results={
              resultsWithRatingMap.resultsWithRatings
              ->Belt.List.keep(r => r.result.date >= startOfDay)
            }
            resultIdsToHighlight
            temp_showRatings=true
          />
        </Box>
    </>;
  };
};
