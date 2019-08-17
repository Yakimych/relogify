open Utils;

let text = ReasonReact.string;

[@react.component]
let make = (~communityName: string) => {
  let (date, setDate) = React.useState(_ => Js.Date.make());
  // TODO: addWeeks(1)
  let incrementWeek = _ => setDate(d => d);
  // TODO: addWeeks(-1)
  let decrementWeek = _ => setDate(d => d);
  // TODO: startOfWeek
  let startDate = Js.Date.make();
  // TODO: endOfWeek
  let endDate = Js.Date.make();

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
          setDate(_ => Js.Date.fromString(ReactEvent.Form.target(e)##value))
        }
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
