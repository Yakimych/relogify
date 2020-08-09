open Utils;
open LeaderboardUtils;
open Types;
open Queries;
open Styles;
open EloUtils;

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

module Query = [%relay.query
  {|
    query StatsQuery(
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
        edges {
          node {
            player1 {
              id
              name
            }
            player2 {
              id
              name
            }
            player2goals
            player1goals
            extratime
            date
            id
          }
        }
      }
    
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...StatsTableHeader_ScoreType
          }
        }
      }
    }
  |}
];

[@react.component]
let make =
    (
      ~communityName: string,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~playerLimit: option(int)=?,
      ~title: option(string)=?,
    ) => {
  let queryData =
    Query.use(~variables={communityName, dateFrom, dateTo}, ());

  let (sortBy, setSortBy) = React.useState(_ => WinsPerMatch);
  let (sortDirection, setSortDirection) = React.useState(_ => `Desc);

  let requestSort = (columnType: columnType) => {
    setSortBy(_ => columnType);
    setSortDirection(currentDirection => currentDirection);
  };
  let results = queryData.results_connection.edges |> toListOfResults4;
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

  let scoreTypeFragment =
    queryData.community_settings_connection.edges->Belt.Array.getExn(0).node.
      fragmentRefs;

  let isWide = MaterialUi.Core.useMediaQueryString("(min-width: 600px)");
  <>
    {leaderboardRows->Belt.List.length === 0
       ? React.null
       : <MaterialUi.Paper>
           <div className="title">
             <MaterialUi.Typography variant=`H6>
               {text(title->Belt.Option.getWithDefault("Stats"))}
             </MaterialUi.Typography>
           </div>
           <MaterialUi.Table size=`Small>
             <StatsTableHeader
               requestSort
               sortBy
               sortDirection
               scoreTypeFragment
               resultsWithRatings
               ?dateFrom
               ?dateTo
             />
             <MaterialUi.TableBody>
               {leaderboardRows
                ->Belt.List.take(maxNumberOfRowsToShow)
                ->Belt.Option.getWithDefault(leaderboardRows)
                ->Belt.List.map(r =>
                    <MaterialUi.TableRow key={r.playerName}>
                      <MaterialUi.TableCell align=`Right>
                        <RouteLink
                          toPage={PlayerHome(communityName, r.playerName)}
                          style=playerLinkStyle>
                          {text(r.playerName)}
                        </RouteLink>
                      </MaterialUi.TableCell>
                      {showEloRatings && isWide
                         ? <MaterialUi.TableCell style=numberCellStyle>
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
                           </MaterialUi.TableCell>
                         : React.null}
                      <MaterialUi.TableCell style=numberCellStyle>
                        {text(formatPercentage(r |> matchesWonPerPlayed))}
                      </MaterialUi.TableCell>
                      <MaterialUi.TableCell style=numberCellStyle>
                        {text(string_of_int(r.matchesWon))}
                      </MaterialUi.TableCell>
                      <MaterialUi.TableCell style=numberCellStyle>
                        {text(string_of_int(r.matchesLost))}
                      </MaterialUi.TableCell>
                      <MaterialUi.TableCell style=numberCellStyle>
                        {text(string_of_int(r.goalsScored))}
                      </MaterialUi.TableCell>
                      <MaterialUi.TableCell style=numberCellStyle>
                        {text(string_of_int(r.goalsConceded))}
                      </MaterialUi.TableCell>
                      {isWide
                         ? <>
                             <MaterialUi.TableCell style=numberCellStyle>
                               {text(r |> goalDiff |> formatDiff)}
                             </MaterialUi.TableCell>
                             <MaterialUi.TableCell style=numberCellStyle>
                               {text(
                                  formatGoalsPerMatch(
                                    r |> goalsScoredPerMatch,
                                  ),
                                )}
                             </MaterialUi.TableCell>
                             <MaterialUi.TableCell style=numberCellStyle>
                               {text(
                                  formatGoalsPerMatch(
                                    r |> goalsConcededPerMatch,
                                  ),
                                )}
                             </MaterialUi.TableCell>
                           </>
                         : React.null}
                    </MaterialUi.TableRow>
                  )
                ->Array.of_list
                ->React.array}
             </MaterialUi.TableBody>
           </MaterialUi.Table>
         </MaterialUi.Paper>}
  </>;
};
