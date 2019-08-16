[@react.component]
let make = (~communityName) => {
  let now = Js.Date.make();
  // TODO: startOfWeek(now, { weekStartsOn: 1});
  let startDate = Js.Date.make();
  // TODO: startOfWeek(endOfWeek, { weekStartsOn: 1});
  let endDate = Js.Date.make();

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
