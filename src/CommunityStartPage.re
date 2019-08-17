open DateFns;

[@react.component]
let make = (~communityName) => {
  let now = Js.Date.make();
  let startDate = now->startOfWeek({"weekStartsOn": 1});
  let endDate = now->addWeeks(1.0);

  <>
    <WeeklyLeaderboard communityName dateFrom=startDate dateTo=endDate />
    <ExpansionPanel>
      <ExpansionPanelSummary expandIcon={<ExpandMoreIcon />}>
        <Fab size="small" color="primary"> <AddIcon /> </Fab>
      </ExpansionPanelSummary>
      <AddResult communityName dateFrom=startDate dateTo=endDate />
    </ExpansionPanel>
    <Results
      communityName
      dateFrom=startDate
      dateTo=endDate
      highlightNewResults=true
    />
    <Link url={"/" ++ communityName ++ "/history"}>
      {ReasonReact.string("All Results")}
    </Link>
  </>;
};
