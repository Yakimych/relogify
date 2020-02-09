open Utils;
open PlayerStatsUtils;
open Types;
open Queries;
open EloUtils;
open ApolloHooks;

[@react.component]
let make = (~communityName, ~player1Name, ~player2Name) => {
  let (headToHeadQuery, _) =
    useQuery(
      ~variables=
        HeadToHeadQuery.makeVariables(
          ~communityName,
          ~player1Name,
          ~player2Name,
          (),
        ),
      HeadToHeadQuery.definition,
    );

  <>
    <Header page={HeadToHead(communityName, player1Name, player2Name)} />
    {switch (headToHeadQuery) {
     | Loading => <MaterialUi_CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let results = data##results |> toListOfResults;
       let stats = getPlayerStats(player1Name, results);
       let resultsWithRatings = results |> attachRatings;

       <>
         <Box textAlign="center">
           <Typography variant="h4">
             {text(player1Name ++ " vs " ++ player2Name)}
           </Typography>
           <div>
             <span className="stats-player-goals">
               {text("(" ++ string_of_int(stats.goalsScored) ++ ")")}
             </span>
             {text(" ")}
             <span className="stats-player-wins">
               {text(
                  string_of_int(stats.matchesWon)
                  ++ " - "
                  ++ string_of_int(stats.matchesLost),
                )}
             </span>
             {text(" ")}
             <span className="stats-player-goals">
               {text("(" ++ string_of_int(stats.goalsConceded) ++ ")")}
             </span>
           </div>
         </Box>
         <ReactMinimalPieChart
           data=[|
             {
               "title": player1Name,
               "value": stats.matchesWon,
               "color": "#00cc00",
             },
             {
               "title": player2Name,
               "value": stats.matchesLost,
               "color": "#ff2200",
             },
           |]
           style={ReactDOMRe.Style.make(
             ~height="100px",
             ~marginBottom="10px",
             (),
           )}
           animate=true
           lineWidth=80
           label=true
           labelStyle={ReactDOMRe.Style.make(
             ~fontSize="20px",
             ~fill="#ffffff",
             (),
           )}
         />
         <ResultsTable
           results={resultsWithRatings.resultsWithRatings}
           communityName
         />
       </>;
     }}
  </>;
};
