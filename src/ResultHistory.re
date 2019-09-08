open Utils;
open DateFns;

let nextPrevWeekButtonStyle =
  ReactDOMRe.Style.make(
    ~width="50px",
    ~minWidth="50px",
    ~marginRight="4px",
    (),
  );

[@react.component]
let make = (~communityName: string) => {
  let weekStartDate = Js.Date.make()->startOfWeek({"weekStartsOn": 1});

  let (dateFrom, setDateFrom) = React.useState(_ => Some(weekStartDate));
  let (dateTo, setDateTo) =
    React.useState(_ => Some(weekStartDate->addWeeks(1.0)));

  let setToday = _ => {
    setDateFrom(_ => Some(weekStartDate));
    setDateTo(_ => Some(weekStartDate->addWeeks(1.0)));
  };

  let setAllTime = _ => {
    setDateFrom(_ => None);
    setDateTo(_ => None);
  };

  let incrementWeek = _ => {
    setDateFrom(df => df->Belt.Option.map(d => d->addWeeks(1.0)));
    setDateTo(dt => dt->Belt.Option.map(d => d->addWeeks(1.0)));
  };

  let decrementWeek = _ => {
    setDateFrom(df => df->Belt.Option.map(d => d->addWeeks(-1.0)));
    setDateTo(dt => dt->Belt.Option.map(d => d->addWeeks(-1.0)));
  };

  <>
    <Header page={History(communityName)} />
    <Box margin="10px" textAlign="center">
      <Box margin="10px" textAlign="center">
        <Button variant="contained" onClick=setAllTime>
          {text("All time")}
        </Button>
        <Button variant="contained" onClick=setToday>
          {text("This week")}
        </Button>
      </Box>
      <Button
        style=nextPrevWeekButtonStyle
        variant="contained"
        onClick=decrementWeek>
        {text("<<")}
      </Button>
      <TextField
        _type="date"
        value={dateFrom->Belt.Option.mapWithDefault("", formatDate)}
        onChange={e => {
          let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
          if (DateFns.isValid(date)) {
            setDateFrom(_ => Some(date));
          };
        }}
      />
      <TextField
        _type="date"
        value={dateTo->Belt.Option.mapWithDefault("", formatDate)}
        onChange={e => {
          let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
          if (DateFns.isValid(date)) {
            setDateTo(_ => Some(date));
          };
        }}
      />
      <Button
        style=nextPrevWeekButtonStyle
        variant="contained"
        onClick=incrementWeek>
        {text(">>")}
      </Button>
    </Box>
    <Stats communityName ?dateFrom ?dateTo />
    <Results
      communityName
      ?dateFrom
      ?dateTo
      highlightNewResults=false
      temp_showRatings={
        dateFrom->Belt.Option.isNone && dateTo->Belt.Option.isNone
      }
    />
  </>;
};
