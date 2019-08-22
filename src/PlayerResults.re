open Utils;
open Types;
open Queries;

type playerStats = {
  numberOfWins: int,
  numberOfLosses: int,
  goalsScored: int,
  goalsConceded: int,
  streaks,
};

[@react.component]
let make = (~playerName: string, ~communityName: string) => {
  let playerResultsQuery =
    PlayerResultsQueryConfig.make(~communityName, ~playerName, ());

  let (playerResultsQuery, _) =
    PlayerResultsQuery.use(~variables=playerResultsQuery##variables, ());

  let playerStats: playerStats = {
    numberOfWins: 3,
    numberOfLosses: 1,
    goalsScored: 22,
    goalsConceded: 11,
    streaks: {
      longestStreak: None,
      currentStreak: None,
    },
  };

  <div>
    <Link url={"/" ++ communityName}> {text("Start Page")} </Link>
    {switch (playerResultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       <>
         <Box textAlign="center">
           <Typography variant="h5"> {text("Player results")} </Typography>
           <Typography variant="h4"> {text(playerName)} </Typography>
           <Typography>
             {text("Total wins: " ++ string_of_int(playerStats.numberOfWins))}
           </Typography>
           <Typography>
             {text(
                "Total losses: " ++ string_of_int(playerStats.numberOfLosses),
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
           {playerStats.streaks.longestStreak
            ->Belt.Option.mapWithDefault(ReasonReact.null, streak =>
                <StreakView
                  streak
                  streakName="Longest winning streak"
                  playerName
                />
              )}
           {playerStats.streaks.currentStreak
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
       </>
     }}
  </div>;
};
