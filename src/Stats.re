open Utils;
open LeaderboardUtils;
open Types;
open Queries;
open Styles;
open EloUtils;

type columnType =
  | EloRating(eloMap)
  | WinsPerMatch
  | MatchesWon
  | MatchesLost
  | GoalsScored
  | GoalsConceded
  | GoalDiff
  | GoalsScoredPerMatch
  | GoalsConcededPerMatch;

type sortDirection =
  | Asc
  | Desc;

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
    ) => {
  let allResultsQuery =
    AllResultsQueryConfig.make(
      ~communityName,
      ~dateFrom=?dateFrom->Belt.Option.map(toJsonDate),
      ~dateTo=?dateTo->Belt.Option.map(toJsonDate),
      (),
    );

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  let (sortBy, setSortBy) = React.useState(_ => WinsPerMatch);
  let (sortDirection, setSortDirection) = React.useState(_ => Desc);

  let requestSort = (columnType: columnType) => {
    setSortBy(_ => columnType);
    setSortDirection(currentDirection =>
      currentDirection === Asc ? Desc : Asc
    );
  };

  <>
    {switch (resultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let results = data##results |> toRecord;
       let showEloRatings =
         dateFrom->Belt.Option.isNone && dateTo->Belt.Option.isNone;

       let resultsWithRatings = results |> attachRatings;

       let leaderboardRows =
         getLeaderboard(results)
         ->Belt.List.keep(includedInStats)
         ->Belt.List.sort(getSortFunc(sortBy, sortDirection));

       leaderboardRows->Belt.List.length === 0
         ? ReasonReact.null
         : <Paper style=containerStyle>
             <Typography variant="h6"> {text("Stats")} </Typography>
             <Table style=containerStyle size="small">
               <TableHead>
                 <TableRow>
                   <TableCell align="right"> {text("Player")} </TableCell>
                   {showEloRatings
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
                      : ReasonReact.null}
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
                   <TableCell style=numberCellStyle title="Goals scored">
                     <TableSortLabel
                       active={sortBy === GoalsScored}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsScored)}>
                       {text("GS")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title="Goals conceded">
                     <TableSortLabel
                       active={sortBy === GoalsConceded}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsConceded)}>
                       {text("GC")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell style=numberCellStyle title="Goal difference">
                     <TableSortLabel
                       active={sortBy === GoalDiff}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalDiff)}>
                       {text("+/-")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell
                     style=numberCellStyle title="Goals scored per match">
                     <TableSortLabel
                       active={sortBy === GoalsScoredPerMatch}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsScoredPerMatch)}>
                       {text("G/M")}
                     </TableSortLabel>
                   </TableCell>
                   <TableCell
                     style=numberCellStyle title="Goals conceded per match">
                     <TableSortLabel
                       active={sortBy === GoalsConcededPerMatch}
                       direction={sortDirection === Asc ? "asc" : "desc"}
                       onClick={_ => requestSort(GoalsConcededPerMatch)}>
                       {text("C/M")}
                     </TableSortLabel>
                   </TableCell>
                 </TableRow>
               </TableHead>
               <TableBody>
                 {leaderboardRows
                  ->Belt.List.map(r =>
                      <TableRow key={r.playerName}>
                        <TableCell align="right">
                          <Link
                            url={"/" ++ communityName ++ "/" ++ r.playerName}
                            style=playerLinkStyle>
                            {text(r.playerName)}
                          </Link>
                        </TableCell>
                        {showEloRatings
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
                           : ReasonReact.null}
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
                        <TableCell style=numberCellStyle>
                          {text(r |> goalDiff |> formatDiff)}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(
                             formatGoalsPerMatch(r |> goalsScoredPerMatch),
                           )}
                        </TableCell>
                        <TableCell style=numberCellStyle>
                          {text(
                             formatGoalsPerMatch(r |> goalsConcededPerMatch),
                           )}
                        </TableCell>
                      </TableRow>
                    )
                  ->Array.of_list
                  ->ReasonReact.array}
               </TableBody>
             </Table>
           </Paper>;
     }}
  </>;
};
