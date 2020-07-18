open DateFns;
open Utils;
open EloUtils;
open Queries;
open Subscriptions;
open ApolloHooks;

[@react.component]
let make = (~communityName: string) => {
  let now = Js.Date.make();
  let startOfDay = now->startOfDay;
  let weekStartDate = now->startOfWeek({"weekStartsOn": 1});
  let monthStartDate = now->startOfMonth;
  let yearStartDate = now->startOfYear;

  let (resultsQuery, fullResultsQuery) =
    useQuery(
      ~variables=AllResultsQuery.makeVariables(~communityName, ()),
      AllResultsQuery.definition,
    );

  let newResultSubscription = NewResultSubscription.make(~communityName, ());
  let newResultDocument = ApolloClient.gql(. newResultSubscription##query);
  let (newResult, setNewResult) = React.useState(_ => None);

  React.useEffect1(
    () => {
      let unsubscribe =
        fullResultsQuery.subscribeToMore(
          ~document=newResultDocument,
          ~variables=newResultSubscription##variables,
          ~updateQuery=
            (prev, subscriptionDataParent) => {
              let maybePrevResults =
                prev |> toAllResults |> Js.Nullable.toOption;
              let maybeNewestResults =
                subscriptionDataParent##subscriptionData##data
                ->toSubscriptionData
                ->Js.Nullable.toOption
                ->Belt.Option.map(s => s.newest_result);

              switch (maybePrevResults, maybeNewestResults) {
              | (Some(prevResults), Some([|newResult|]))
                  when
                    prevResults.results
                    ->Belt.Array.every(r => r.id !== newResult.id) =>
                setNewResult(_ => Some(newResult.id));
                {
                  results:
                    prevResults.results->Belt.Array.concat([|newResult|]),
                }
                ->allResultsToJson;
              | _ => prev
              };
            },
          (),
        );
      Some(unsubscribe);
    },
    [|communityName|],
  );

  switch (resultsQuery) {
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let results = data##results |> toListOfResults;
    let resultsWithRatingMap = results |> attachRatings;
    let resultIdsToHighlight =
      newResult->Belt.Option.mapWithDefault([], v => [v]);

    <>
      <Header page={TopX(communityName)} />
      <MaterialUi.Box margin="10px" textAlign="center">
        <TopStats
          communityName
          title="This Week"
          resultsWithMap=resultsWithRatingMap
          startDate=weekStartDate
        />
        <TopStats
          communityName
          title="This Month"
          resultsWithMap=resultsWithRatingMap
          startDate=monthStartDate
        />
        <TopStats
          communityName
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
      </MaterialUi.Box>
    </>;
  };
};
