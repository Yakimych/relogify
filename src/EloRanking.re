open Styles;
open Utils;
open EloUtils;
open Queries;

[@react.component]
let make = (~communityName: string) => {
  let allResultsQuery = AllResultsQueryConfig.make(~communityName, ());

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  <Paper style=containerStyle>
    <Badge badgeContent="BETA" color="primary">
      <Typography variant="h6"> {text("Elo rankings")} </Typography>
    </Badge>
    {switch (resultsQuery) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {text("Error")} </span>
     | Data(data) =>
       let eloRatings = getEloRankings(data##results |> toRecord);

       <Table size="small">
         <TableHead>
           <TableRow>
             <TableCell align="right"> {text("Player")} </TableCell>
             <TableCell style=numberCellStyle> {text("Rating")} </TableCell>
           </TableRow>
         </TableHead>
         <TableBody>
           {eloRatings->Belt.List.map(((playerName, rating)) =>
              <TableRow key=playerName>
                <TableCell align="right">
                  <Link
                    url={"/" ++ communityName ++ "/" ++ playerName}
                    style=playerLinkStyle>
                    {text(playerName)}
                  </Link>
                </TableCell>
                <TableCell align="right">
                  {text(Js.Float.toString(Js.Math.round(rating)))}
                </TableCell>
              </TableRow>
            )
            |> Array.of_list
            |> ReasonReact.array}
         </TableBody>
       </Table>;
     }}
    <Link url={"/" ++ communityName}> {text("Back to Start Page")} </Link>
  </Paper>;
};
