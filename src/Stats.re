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
    sortDirection === Asc ? 1 : (-1);
  } else if (valueFromRow1ToCompare < valueFromRow2ToCompare) {
    sortDirection === Asc ? (-1) : 1;
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
  let (sortDirection, setSortDirection) = React.useState(_ => Desc);

  let requestSort = (columnType: columnType) => {
    setSortBy(_ => columnType);
    setSortDirection(currentDirection =>
      currentDirection === Asc ? Desc : Asc
    );
  };

  let isWide = MaterialUi.useMediaQuery("(min-width: 600px)");
  <>
    {switch (resultsQuery, settingsQuery) {
     | (_, Loading)
     | (Loading, _) => <CircularProgress />
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
               <Typography variant="h6">
                 {text(title->Belt.Option.getWithDefault("Stats"))}
               </Typography>
             </div>
             <Table size="small">
               <TableHead>
                 <TableRow>
                   <TableCell align="right"> {text("Player")} </TableCell>
                   {showEloRatings && isWide
                      ? <>
                          <Badge badgeContent="BETA" color="primary">
                            <TableCell
                              style=numberCellStyle title="Elo Rating">
                              <TableSortLabel
                                active={
                                  sortBy
                                  == EloRating(resultsWithRatings.ratingMap)
                                }
                                direction={
                                  sortDirection === Asc ? "asc" : "desc"
                                }
                                onClick={_ =>
                                  requestSort(
                                    EloRating(resultsWithRatings.ratingMap),
                                  )
                                }>
                                {text("Elo")}
                              </TableSortLabel>
                            </TableCell>
                          </Badge>
                        </>
                      : React.null}
                   <TableCell style=numberCellStyle title="Win Percentage">
                     <TableSortLabel
                       active={sortBy === WinsPerMatch}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(WinsPerMatch)}>
                       {text("W%")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title="Number of wins">
                     <TableSortLabel
                       active={sortBy === MatchesWon}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(MatchesWon)}>
                       {text("W")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title="Number of losses">
                     <TableSortLabel
                       active={sortBy === MatchesLost}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(MatchesLost)}>
                       {text("L")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title={texts.pointsWon}>
                     <TableSortLabel
                       active={sortBy === GoalsScored}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsScored)}>
                       {text(texts.pointsWonShort)}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title={texts.pointsLost}>
                     <TableSortLabel
                       active={sortBy === GoalsConceded}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsConceded)}>
                       {text(texts.pointsLostShort)}
                     </TableSortLabel>
                   </TableCell>
                   {isWide
                      ? <>
                          <TableCell
                            style=numberCellStyle title={texts.pointDiff}>
                            <TableSortLabel
                              active={sortBy === GoalDiff}
                              direction={
                                sortDirection === Asc ? "asc" : "desc"
                              }
                              onClick={_ => requestSort(GoalDiff)}>
                              {text("+/-")}
                            </TableSortLabel>
                          </TableCell>
                          <TableCell
                            style=numberCellStyle
                            title={texts.pointsWonPerMatch}>
                            <TableSortLabel
                              active={sortBy === GoalsScoredPerMatch}
                              direction={
                                sortDirection === Asc ? "asc" : "desc"
                              }
                              onClick={_ => requestSort(GoalsScoredPerMatch)}>
                              {text(texts.pointsWonPerMatchShort)}
                            </TableSortLabel>
                          </TableCell>
                          <TableCell
                            style=numberCellStyle
                            title={texts.pointsLostPerMatch}>
                            <TableSortLabel
                              active={sortBy === GoalsConcededPerMatch}
                              direction={
                                sortDirection === Asc ? "asc" : "desc"
                              }
                              onClick={_ =>
                                requestSort(GoalsConcededPerMatch)
                              }>
                              {text(texts.pointsLostPerMatchShort)}
                            </TableSortLabel>
                          </TableCell>
                        </>
                      : React.null}
                 </TableRow>
               </TableHead>
               <TableBody>
                 {leaderboardRows
                  ->Belt.List.take(maxNumberOfRowsToShow)
                  ->Belt.Option.getWithDefault(leaderboardRows)
                  ->Belt.List.map(r =>
                      <TableRow key={r.playerName}>
                        <TableCell align="right">
                          <RouteLink
                            toPage={PlayerHome(communityName, r.playerName)}
                            style=playerLinkStyle>
                            {text(r.playerName)}
                          </RouteLink>
                        </TableCell>
                        {showEloRatings && isWide
                           ? <TableCell style=numberCellStyle>
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
                             </TableCell>
                           : React.null}
                        <TableCell style=numberCellStyle>
                          {text(formatPercentage(r |> matchesWonPerPlayed))}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(string_of_int(r.matchesWon))}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(string_of_int(r.matchesLost))}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(string_of_int(r.goalsScored))}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(string_of_int(r.goalsConceded))}
                        </TableCell>
                        {isWide
                           ? <>
                               <TableCell style=numberCellStyle>
                                 {text(r |> goalDiff |> formatDiff)}
                               </TableCell>
                               <TableCell style=numberCellStyle>
                                 {text(
                                    formatGoalsPerMatch(
                                      r |> goalsScoredPerMatch,
                                    ),
                                  )}
                               </TableCell>
                               <TableCell style=numberCellStyle>
                                 {text(
                                    formatGoalsPerMatch(
                                      r |> goalsConcededPerMatch,
                                    ),
                                  )}
                               </TableCell>
                             </>
                           : React.null}
                      </TableRow>
                    )
                  ->Array.of_list
                  ->React.array}
               </TableBody>
             </Table>
           </MaterialUi_Paper>;
     }}
  </>;
};
