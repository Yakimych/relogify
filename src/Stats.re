open Utils;
open LeaderboardUtils;
open Types;
open Queries;
open Styles;
open EloUtils;
open UseCommunitySettings;
open ApolloHooks;

let getValueToCompareFunc = (sortBy: columnType) => {
  switch (sortBy) {
  | EloRating(ratingsMap) => (
      (row: playerStats) => {
        ratingsMap
        ->Belt_MapString.get(row.playerName)
        ->Belt.Option.getWithDefault(0.0);
      }
    )
  | WinsPerMatch => ((row: playerStats) => row |> matchesWonPerPlayed)
  | MatchesWon => ((row: playerStats) => float_of_int(row.matchesWon))
  | MatchesLost => ((row: playerStats) => float_of_int(row.matchesLost))
  | GoalsScored => ((row: playerStats) => float_of_int(row.goalsScored))
  | GoalsConceded => ((row: playerStats) => float_of_int(row.goalsConceded))
  | GoalDiff => ((row: playerStats) => float_of_int(row |> goalDiff))
  | GoalsScoredPerMatch => ((row: playerStats) => row |> goalsScoredPerMatch)
  | GoalsConcededPerMatch => (
      (row: playerStats) => row |> goalsConcededPerMatch
    )
  };
};

let getSortFunc =
    (
      sortBy: columnType,
      sortDirection: sortDirection,
      row1: playerStats,
      row2: playerStats,
    ) => {
  let getValueToCompare = getValueToCompareFunc(sortBy);

  let valueFromRow1ToCompare = getValueToCompare(row1);
  let valueFromRow2ToCompare = getValueToCompare(row2);

  if (valueFromRow1ToCompare > valueFromRow2ToCompare) {
    sortDirection === `Asc ? 1 : (-1);
  } else if (valueFromRow1ToCompare < valueFromRow2ToCompare) {
    sortDirection === `Asc ? (-1) : 1;
  } else {
    0;
  };
};

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~playerLimit: option(int)=?,
      ~title: option(string)=?,
    ) => {
  let (resultsQuery, _) =
    useQuery(
      ~variables=
        AllResultsQuery.makeVariables(
          ~communityName,
          ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
          ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
          (),
        ),
      AllResultsQuery.definition,
    );

  let settingsQuery = useCommunitySettings(communityName);

  let (sortBy, setSortBy) = React.useState(_ => WinsPerMatch);
  let (sortDirection, setSortDirection) = React.useState(_ => `Desc);

  let requestSort = (columnType: columnType) => {
    setSortBy(_ => columnType);
    setSortDirection(currentDirection => currentDirection);
  };

  let isWide = MaterialUi.useMediaQuery("(min-width: 600px)");
  <>
    {switch (resultsQuery, settingsQuery) {
     | (_, Loading)
     | (Loading, _) => <MaterialUi_CircularProgress />
     | (NoData, _)
     | (_, NoData)
     | (Error(_), _)
     | (_, Error(_)) => <span> {text("Error")} </span>
     | (Data(resultsData), Data(communitySettings)) =>
       let results = resultsData##results |> toListOfResults;
       let texts = Texts.getScoreTypeTexts(communitySettings.scoreType);

       let showEloRatings =
         dateFrom->Belt.Option.isNone && dateTo->Belt.Option.isNone;

       let resultsWithRatings = results |> attachRatings;

       let leaderboardRows =
         getLeaderboard(results)
         ->Belt.List.keep(includedInStats)
         ->Belt.List.sort(getSortFunc(sortBy, sortDirection));

       let maxNumberOfRowsToShow =
         playerLimit->Belt.Option.getWithDefault(
           leaderboardRows->Belt.List.length,
         );

       leaderboardRows->Belt.List.length === 0
         ? React.null
         : <MaterialUi_Paper>
             <div className="title">
               <MaterialUi_Typography variant=`H6>
                 {text(title->Belt.Option.getWithDefault("Stats"))}
               </MaterialUi_Typography>
             </div>
             <MaterialUi_Table size=`Small>
               <MaterialUi_TableHead>
                 <MaterialUi_TableRow>
                   <MaterialUi_TableCell align=`Right>
                     {text("Player")}
                   </MaterialUi_TableCell>
                   {showEloRatings && isWide
                      ? <>
                          <MaterialUi_Badge
                            badgeContent={React.string("BETA")}
                            color=`Primary>
                            <MaterialUi_TableCell style=numberCellStyle>
                              //  TODO: title="Elo Rating"

                                <MaterialUi_TableSortLabel
                                  active={
                                    sortBy
                                    == EloRating(resultsWithRatings.ratingMap)
                                  }
                                  direction=sortDirection
                                  onClick={_ =>
                                    requestSort(
                                      EloRating(resultsWithRatings.ratingMap),
                                    )
                                  }>
                                  {text("Elo")}
                                </MaterialUi_TableSortLabel>
                              </MaterialUi_TableCell>
                          </MaterialUi_Badge>
                        </>
                      : React.null}
                   <MaterialUi_TableCell style=numberCellStyle>
                     // TODO:  title="Win Percentage">

                       <MaterialUi_TableSortLabel
                         active={sortBy === WinsPerMatch}
                         direction=sortDirection
                         onClick={_ => requestSort(WinsPerMatch)}>
                         {text("W%")}
                       </MaterialUi_TableSortLabel>
                     </MaterialUi_TableCell>
                   <MaterialUi_TableCell style=numberCellStyle>
                     //  TODO: title="Number of wins">

                       <MaterialUi_TableSortLabel
                         active={sortBy === MatchesWon}
                         direction=sortDirection
                         onClick={_ => requestSort(MatchesWon)}>
                         {text("W")}
                       </MaterialUi_TableSortLabel>
                     </MaterialUi_TableCell>
                   <MaterialUi_TableCell style=numberCellStyle>
                     // TODO:  title="Number of losses">

                       <MaterialUi_TableSortLabel
                         active={sortBy === MatchesLost}
                         direction=sortDirection
                         onClick={_ => requestSort(MatchesLost)}>
                         {text("L")}
                       </MaterialUi_TableSortLabel>
                     </MaterialUi_TableCell>
                   <MaterialUi_TableCell style=numberCellStyle>
                     // TODO: title={texts.pointsWon}>

                       <MaterialUi_TableSortLabel
                         active={sortBy === GoalsScored}
                         direction=sortDirection
                         onClick={_ => requestSort(GoalsScored)}>
                         {text(texts.pointsWonShort)}
                       </MaterialUi_TableSortLabel>
                     </MaterialUi_TableCell>
                   <MaterialUi_TableCell style=numberCellStyle>
                     // TODO: title={texts.pointsLost}>

                       <MaterialUi_TableSortLabel
                         active={sortBy === GoalsConceded}
                         direction=sortDirection
                         onClick={_ => requestSort(GoalsConceded)}>
                         {text(texts.pointsLostShort)}
                       </MaterialUi_TableSortLabel>
                     </MaterialUi_TableCell>
                   {isWide
                      ? <>
                          <MaterialUi_TableCell style=numberCellStyle>
                            // TODO: title={texts.pointDiff}>

                              <MaterialUi_TableSortLabel
                                active={sortBy === GoalDiff}
                                direction=sortDirection
                                onClick={_ => requestSort(GoalDiff)}>
                                {text("+/-")}
                              </MaterialUi_TableSortLabel>
                            </MaterialUi_TableCell>
                          <MaterialUi_TableCell style=numberCellStyle>
                            // TODO: title={texts.pointsWonPerMatch}>

                              <MaterialUi_TableSortLabel
                                active={sortBy === GoalsScoredPerMatch}
                                direction=sortDirection
                                onClick={_ =>
                                  requestSort(GoalsScoredPerMatch)
                                }>
                                {text(texts.pointsWonPerMatchShort)}
                              </MaterialUi_TableSortLabel>
                            </MaterialUi_TableCell>
                          <MaterialUi_TableCell style=numberCellStyle>
                            // TODO: title={texts.pointsLostPerMatch}>

                              <MaterialUi_TableSortLabel
                                active={sortBy === GoalsConcededPerMatch}
                                direction=sortDirection
                                onClick={_ =>
                                  requestSort(GoalsConcededPerMatch)
                                }>
                                {text(texts.pointsLostPerMatchShort)}
                              </MaterialUi_TableSortLabel>
                            </MaterialUi_TableCell>
                        </>
                      : React.null}
                 </MaterialUi_TableRow>
               </MaterialUi_TableHead>
               <MaterialUi_TableBody>
                 {leaderboardRows
                  ->Belt.List.take(maxNumberOfRowsToShow)
                  ->Belt.Option.getWithDefault(leaderboardRows)
                  ->Belt.List.map(r =>
                      <MaterialUi_TableRow key={r.playerName}>
                        <MaterialUi_TableCell align=`Right>
                          <RouteLink
                            toPage={PlayerHome(communityName, r.playerName)}
                            style=playerLinkStyle>
                            {text(r.playerName)}
                          </RouteLink>
                        </MaterialUi_TableCell>
                        {showEloRatings && isWide
                           ? <MaterialUi_TableCell style=numberCellStyle>
                               {text(
                                  resultsWithRatings.ratingMap
                                  ->Belt_MapString.getWithDefault(
                                      r.playerName,
                                      initialRating,
                                    )
                                  |> Js.Math.round
                                  |> int_of_float
                                  |> string_of_int,
                                )}
                             </MaterialUi_TableCell>
                           : React.null}
                        <MaterialUi_TableCell style=numberCellStyle>
                          {text(formatPercentage(r |> matchesWonPerPlayed))}
                        </MaterialUi_TableCell>
                        <MaterialUi_TableCell style=numberCellStyle>
                          {text(string_of_int(r.matchesWon))}
                        </MaterialUi_TableCell>
                        <MaterialUi_TableCell style=numberCellStyle>
                          {text(string_of_int(r.matchesLost))}
                        </MaterialUi_TableCell>
                        <MaterialUi_TableCell style=numberCellStyle>
                          {text(string_of_int(r.goalsScored))}
                        </MaterialUi_TableCell>
                        <MaterialUi_TableCell style=numberCellStyle>
                          {text(string_of_int(r.goalsConceded))}
                        </MaterialUi_TableCell>
                        {isWide
                           ? <>
                               <MaterialUi_TableCell style=numberCellStyle>
                                 {text(r |> goalDiff |> formatDiff)}
                               </MaterialUi_TableCell>
                               <MaterialUi_TableCell style=numberCellStyle>
                                 {text(
                                    formatGoalsPerMatch(
                                      r |> goalsScoredPerMatch,
                                    ),
                                  )}
                               </MaterialUi_TableCell>
                               <MaterialUi_TableCell style=numberCellStyle>
                                 {text(
                                    formatGoalsPerMatch(
                                      r |> goalsConcededPerMatch,
                                    ),
                                  )}
                               </MaterialUi_TableCell>
                             </>
                           : React.null}
                      </MaterialUi_TableRow>
                    )
                  ->Array.of_list
                  ->React.array}
               </MaterialUi_TableBody>
             </MaterialUi_Table>
           </MaterialUi_Paper>;
     }}
  </>;
};
