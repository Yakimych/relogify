open Utils;
open PlayerStatsUtils;
open Streaks;
open Types;
open Queries;

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let playerResultsQuery =
    PlayerResultsQueryConfig.make(~communityName, ~playerName, ());

  let (playerResultsQuery, _) =
    PlayerResultsQuery.use(~variables=playerResultsQuery##variables, ());

  <div>
    {switch (playerResultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let results = data##results |> toRecord;
       let playerStats: playerStats = getPlayerStats(playerName, results);

       let streaks = getAllStreaks(playerName, results);

       <>
         <Box textAlign="center">
           <Typography variant="h5"> {text("Player results")} </Typography>
           <Typography variant="h4"> {text(playerName)} </Typography>
           <Typography>
             {text("Total wins: " ++ string_of_int(playerStats.matchesWon))}
           </Typography>
           <Typography>
             {text(
                "Total losses: " ++ string_of_int(playerStats.matchesLost),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals scored: "
                ++ string_of_int(playerStats.goalsScored),
              )}
           </Typography>
           <Typography>
             {text(
                "Total goals conceded: "
                ++ string_of_int(playerStats.goalsConceded),
              )}
           </Typography>
           {streaks
            ->getLongestStreak
            ->Belt.Option.mapWithDefault(ReasonReact.null, streak =>
                <StreakView
                  streak
                  streakName="Longest winning streak"
                  playerName
                />
              )}
           {streaks
            ->getCurrentStreak
            ->Belt.Option.mapWithDefault(ReasonReact.null, streak =>
                <StreakView
                  streak
                  streakName="Ongoing winning streak"
                  playerName
                />
              )}
         </Box>
         <ResultsTable
           results={data##results |> toRecord}
           mainPlayerName=playerName
           communityName
         />
       </>;
     }}
    <Link url={"/" ++ communityName}> {text("Start Page")} </Link>
  </div>;
};
