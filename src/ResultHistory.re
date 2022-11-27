open Utils;
open DateFns;

let nextPrevWeekButtonStyle =
  ReactDOMRe.Style.make(
    ~width="50px",
    ~minWidth="50px",
    ~marginRight="4px",
    (),
  );

module Query = [%relay.query
  {|
    query ResultHistoryQuery(
      $communityName: String!
      $dateFrom: timestamptz
      $dateTo: timestamptz
    ) {
      results_connection(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
        ...ResultsTable_Results
        ...Stats_Results
      }
    
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...ResultCommunitySettings_IncludeExtraTime
            ...ResultsTableHeader_CommunitySettings
            ...StatsTableHeader_ScoreType
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName: string) => {
  let weekStartDate =
    Js.Date.make()
    ->DateFns.startOfWeekOpt({locale: None, weekStartsOn: Some(1)});

  let (dateFrom, setDateFrom) = React.useState(_ => Some(weekStartDate));
  let (dateTo, setDateTo) =
    React.useState(_ => Some(weekStartDate->DateFns.addWeeks(1)));

  let setToday = _ => {
    setDateFrom(_ => Some(weekStartDate));
    setDateTo(_ => Some(weekStartDate->DateFns.addWeeks(1)));
  };

  let setAllTime = _ => {
    setDateFrom(_ => None);
    setDateTo(_ => None);
  };

  let incrementWeek = _ => {
    setDateFrom(df => df->Belt.Option.map(d => d->DateFns.addWeeks(1)));
    setDateTo(dt => dt->Belt.Option.map(d => d->DateFns.addWeeks(1)));
  };

  let decrementWeek = _ => {
    setDateFrom(df => df->Belt.Option.map(d => d->DateFns.addWeeks(-1)));
    setDateTo(dt => dt->Belt.Option.map(d => d->DateFns.addWeeks(-1)));
  };

  let queryDateFrom = dateFrom->Belt.Option.mapWithDefault(Js.Date.fromString("2000-01-01"), x => x)
  let queryDateTo = dateTo->Belt.Option.mapWithDefault(Js.Date.fromString("2100-01-01"), x => x)

  let queryData =
    Query.use(~variables={communityName, dateFrom: queryDateFrom, dateTo: queryDateTo}, ());

  let resultsFragment = queryData.results_connection.fragmentRefs;

  let communitySettingsFragments =
    queryData.community_settings_connection.edges
    ->Belt.Array.map(e => e.node.fragmentRefs);

  <>
    <Header page={History(communityName)} />
    <MaterialUi.Box margin="10px" textAlign="center">
      <MaterialUi.Box margin="10px" textAlign="center">
        <MaterialUi.Button variant=`Contained onClick=setAllTime>
          {text("All time")}
        </MaterialUi.Button>
        <MaterialUi.Button variant=`Contained onClick=setToday>
          {text("This week")}
        </MaterialUi.Button>
      </MaterialUi.Box>
      <MaterialUi.Button
        style=nextPrevWeekButtonStyle variant=`Contained onClick=decrementWeek>
        {text("<<")}
      </MaterialUi.Button>
      <MaterialUi.TextField
        type_="date"
        value={`String(dateFrom->Belt.Option.mapWithDefault("", formatDate))}
        onChange={e => {
          let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
          if (DateFns.isValid(date)) {
            setDateFrom(_ => Some(date));
          };
        }}
      />
      <MaterialUi.TextField
        type_="date"
        value={`String(dateTo->Belt.Option.mapWithDefault("", formatDate))}
        onChange={e => {
          let date = Js.Date.fromString(ReactEvent.Form.target(e)##value);
          if (DateFns.isValid(date)) {
            setDateTo(_ => Some(date));
          };
        }}
      />
      <MaterialUi.Button
        style=nextPrevWeekButtonStyle variant=`Contained onClick=incrementWeek>
        {text(">>")}
      </MaterialUi.Button>
    </MaterialUi.Box>
    <React.Suspense fallback={<MaterialUi.CircularProgress />}>
      <Stats
        communityName
        ?dateFrom
        ?dateTo
        statsResultsFragment=resultsFragment
        scoreTypeFragments=communitySettingsFragments
      />
      <ResultsTable
        communityName
        resultsTableFragment=resultsFragment
        communitySettingsFragments
        temp_showRatings={
          dateFrom->Belt.Option.isNone && dateTo->Belt.Option.isNone
        }
      />
    </React.Suspense>
  </>;
};
