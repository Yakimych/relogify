open DateFns;
open Utils;
open EloUtils;
open Queries;
open Subscriptions;

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
      let unsubscribe =
        fullResultsQuery.subscribeToMore(
          ~document=newResultDocument,
          ~variables=newResultSubscription##variables,
          ~updateQuery=[%bs.raw
            {|
            function(prev, { subscriptionData }) {
              if (!prev || subscriptionData.data.newest_result.length === 0) {
                return prev;
              }

              const newestResult = subscriptionData.data.newest_result[0];
              const alreadyInList = prev.results.filter(r => r.id === newestResult.id)[0];
              newResultRef.current = alreadyInList ? undefined : newestResult.id;

              return {
                results: [...(alreadyInList ? [] : [newestResult]), ...prev.results]
              };
            }
          |}
          ],
          (),
        );
      Some(unsubscribe);
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
      <TopStats
        title="This Week"
        resultsWithMap=resultsWithRatingMap
        startDate=weekStartDate
      />
      <TopStats
        title="This Month"
        resultsWithMap=resultsWithRatingMap
        startDate=monthStartDate
      />
      <TopStats
        title="This Year"
        resultsWithMap=resultsWithRatingMap
        startDate=yearStartDate
      />
      {switch (
          resultsWithRatingMap.resultsWithRatings
          ->Belt.List.keep(r => r.result.date >= startOfDay)
        ) {
        | [] => React.null
        | todaysResults =>
          <ResultsTable
            communityName
            results=todaysResults
            resultIdsToHighlight
            temp_showRatings=true
          />
        }}
    </>;
  };
};
