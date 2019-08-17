open Utils;
open Styles;

type extendedLeaderboardRow = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
  matchesWonPerPlayed: int,
  goalsScoredPerMatch: float,
  goalsConcededPerMatch: float,
  goalDiff: int,
};

type columnType =
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
  | WinsPerMatch => (
      (row: extendedLeaderboardRow) => float_of_int(row.matchesWonPerPlayed)
    )
  | MatchesWon => (
      (row: extendedLeaderboardRow) => float_of_int(row.matchesWon)
    )
  | MatchesLost => (
      (row: extendedLeaderboardRow) => float_of_int(row.matchesLost)
    )
  | GoalsScored => (
      (row: extendedLeaderboardRow) => float_of_int(row.goalsScored)
    )
  | GoalsConceded => (
      (row: extendedLeaderboardRow) => float_of_int(row.goalsConceded)
    )
  | GoalDiff => ((row: extendedLeaderboardRow) => float_of_int(row.goalDiff))
  | GoalsScoredPerMatch => (
      (row: extendedLeaderboardRow) => row.goalsScoredPerMatch
    )
  | GoalsConcededPerMatch => (
      (row: extendedLeaderboardRow) => row.goalsConcededPerMatch
    )
  };
};

let getSortFunc =
    (
      sortBy: columnType,
      sortDirection: sortDirection,
      row1: extendedLeaderboardRow,
      row2: extendedLeaderboardRow,
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

let formatGoalDiff = (diff: int) =>
  text((diff > 0 ? "+" : "") ++ string_of_int(diff));

let formatGoalsPerMatch = (goals: float) =>
  text(Js.Float.toFixedWithPrecision(goals, ~digits=1));

let fakeLeaderboardRows: array(extendedLeaderboardRow) = [|
  {
    playerName: "FakePlayer1",
    matchesWon: 5,
    matchesLost: 1,
    goalsScored: 50,
    goalsConceded: 10,
    matchesWonPerPlayed: 60,
    goalsScoredPerMatch: 11.5,
    goalsConcededPerMatch: 5.3,
    goalDiff: (-10),
  },
  {
    playerName: "FakePlayer2",
    matchesWon: 1,
    matchesLost: 1,
    goalsScored: 5,
    goalsConceded: 21,
    matchesWonPerPlayed: 50,
    goalsScoredPerMatch: 1.6666666667,
    goalsConcededPerMatch: 6.9,
    goalDiff: 5,
  },
|];

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
  let (sortBy, setSortBy) = React.useState(_ => WinsPerMatch);
  let (sortDirection, setSortDirection) = React.useState(_ => Desc);

  let requestSort = (columnType: columnType) => {
    setSortBy(_ => columnType);
    setSortDirection(currentDirection =>
      currentDirection === Asc ? Desc : Asc
    );
  };

  let leaderboardRows: list(extendedLeaderboardRow) =
    fakeLeaderboardRows
    |> Array.to_list
    |> List.sort(getSortFunc(sortBy, sortDirection));

  <>
    {leaderboardRows->Belt.List.length === 0
       ? ReasonReact.null
       : <Paper style=containerStyle>
           <Typography variant="h6"> {text("Weekly stats")} </Typography>
           <Table style=containerStyle size="small">
             <TableHead>
               <TableRow>
                 <TableCell align="right"> {text("Player")} </TableCell>
                 <TableCell style=numberCellStyle title="Win Percentage">
                   <TableSortLabel
                     active={sortBy === MatchesWon}
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
                      <TableCell style=numberCellStyle>
                        {text(string_of_int(r.matchesWonPerPlayed) ++ "%")}
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
                        {formatGoalDiff(r.goalDiff)}
                      </TableCell>
                      <TableCell style=numberCellStyle>
                        {formatGoalsPerMatch(r.goalsScoredPerMatch)}
                      </TableCell>
                      <TableCell style=numberCellStyle>
                        {formatGoalsPerMatch(r.goalsConcededPerMatch)}
                      </TableCell>
                    </TableRow>
                  )
                ->Array.of_list
                ->ReasonReact.array}
             </TableBody>
           </Table>
         </Paper>}
  </>;
};
