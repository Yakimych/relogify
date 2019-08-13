open Styles;

let text = ReasonReact.string;

type extendedLeaderboardRow = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
  matchesWonPerPlayed: int,
  goalsScoredPerMatch: int,
  goalsConcededPerMatch: int,
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
  | WinsPerMatch => ((row: extendedLeaderboardRow) => row.matchesWonPerPlayed)
  | MatchesWon => ((row: extendedLeaderboardRow) => row.matchesWon)
  | MatchesLost => ((row: extendedLeaderboardRow) => row.matchesLost)
  | GoalsScored => ((row: extendedLeaderboardRow) => row.goalsScored)
  | GoalsConceded => ((row: extendedLeaderboardRow) => row.goalsConceded)
  | GoalDiff => ((row: extendedLeaderboardRow) => row.goalDiff)
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

let fakeLeaderboardRows: array(extendedLeaderboardRow) = [|
  {
    playerName: "FakePlayer1",
    matchesWon: 5,
    matchesLost: 1,
    goalsScored: 50,
    goalsConceded: 10,
    matchesWonPerPlayed: 60,
    goalsScoredPerMatch: 11,
    goalsConcededPerMatch: 5,
    goalDiff: (-10),
  },
  {
    playerName: "FakePlayer2",
    matchesWon: 1,
    matchesLost: 1,
    goalsScored: 5,
    goalsConceded: 21,
    matchesWonPerPlayed: 50,
    goalsScoredPerMatch: 1,
    goalsConcededPerMatch: 6,
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
                 </TableRow>
                 /*  TODO: Implement the rest */
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
                      </TableRow>
                      /*  TODO: Implement the rest */
                  )
                ->Array.of_list
                ->ReasonReact.array}
             </TableBody>
           </Table>
         </Paper>}
  </>;
};
