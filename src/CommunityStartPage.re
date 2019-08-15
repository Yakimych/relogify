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
      <ExpansionPanelSummary
        expandIcon={<div> {ReasonReact.string("Expand")} </div>}>
        <Fab size="small" color="primary">
          <div> {ReasonReact.string("Add")} </div>
        </Fab>
      </ExpansionPanelSummary>
      <AddResult communityName dateFrom=startDate dateTo=endDate />
    </ExpansionPanel>
  </>;
};
