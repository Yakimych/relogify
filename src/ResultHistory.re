open Utils;
open DateFns;

[@react.component]
let make = (~communityName: string) => {
  let (date, setDate) = React.useState(_ => Js.Date.make());
  let incrementWeek = _ => setDate(d => d->addWeeks(1.0));
  let decrementWeek = _ => setDate(d => d->addWeeks(-1.0));
  let startDate = date->startOfWeek({"weekStartsOn": 1});
  let endDate = startDate->addWeeks(1.0);

  <>
    <Link url={"/" ++ communityName}> {text("Back to Start Page")} </Link>
    <Box margin="10px" textAlign="center">
      <Button variant="contained" onClick=decrementWeek>
        {text("PREV")}
      </Button>
      <TextField
        _type="date"
        value={formatDate(date)}
        onChange={e =>
          // TODO: Validate
          setDate(_ => Js.Date.fromString(ReactEvent.Form.target(e)##value))}
      />
      <Button variant="contained" onClick=incrementWeek>
        {text("NEXT")}
      </Button>
    </Box>
    <Box textAlign="center">
      {text(
         "Results from "
         ++ formatDate(startDate)
         ++ " to "
         ++ formatDate(endDate),
       )}
    </Box>
    <WeeklyLeaderboard communityName dateFrom=startDate dateTo=endDate />
    <Typography variant="h6"> {text("Results")} </Typography>
    <Results
      communityName
      dateFrom=startDate
      dateTo=endDate
      highlightNewResults=false
    />
  </>;
};
