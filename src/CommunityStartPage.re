open Utils;

[@react.component]
let make = (~communityName) => {
  let (startDate, endDate) = getCurrentWeek();

  <>
    <Header page={CommunityStart(communityName)} />
    <Stats communityName dateFrom=startDate dateTo=endDate />
    <Results
      communityName
      dateFrom=startDate
      dateTo=endDate
      highlightNewResults=true
    />
  </>;
};
