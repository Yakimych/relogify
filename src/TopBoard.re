open DateFns;

let topNumberOfRows = 5;

[@react.component]
let make = (~communityName: string) => {
  let now = Js.Date.make();
  let startOfDay = now->startOfDay;
  let weekStartDate = now->startOfWeek({"weekStartsOn": 1});
  let monthStartDate = now->startOfMonth;
  let yearStartDate = now->startOfYear;

  <>
    <Header page={TopX(communityName)} />
    <Box margin="10px" textAlign="center">
      <Stats
        communityName
        dateFrom=weekStartDate
        dateTo=now
        playerLimit=topNumberOfRows
        title="This week"
      />
      <Stats
        communityName
        dateFrom=monthStartDate
        dateTo=now
        playerLimit=topNumberOfRows
        title="This month"
      />
      <Stats
        communityName
        dateFrom=yearStartDate
        dateTo=now
        playerLimit=topNumberOfRows
        title="This year"
      />
      <Results
        communityName
        dateFrom=startOfDay
        dateTo=now
        highlightNewResults=false
      />
    </Box>
  </>;
};
