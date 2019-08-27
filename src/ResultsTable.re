open Styles;
open Utils;
open Types;
open EloUtils;

let getPlayerStyle = (isWinningPlayer: bool) =>
  ReactDOMRe.Style.make(~fontWeight=isWinningPlayer ? "bold" : "normal", ());

let headToHeadStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

let colonStyle =
  ReactDOMRe.Style.make(
    ~width="5px",
    ~paddingLeft="0",
    ~paddingRight="0",
    (),
  );

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

let extraTimeStyle = ReactDOMRe.Style.make(~width="20px", ());

let getHighlightedClassName =
    (newResults: option(list(result)), currentResult: result) => {
  let resultIsFresh =
    newResults
    ->Belt.Option.map(n => n->Belt.List.some(nr => nr == currentResult))
    ->Belt.Option.getWithDefault(false);

  resultIsFresh ? "highlighted" : "";
};

let getWinningLosingRowClassName = (mainPlayerWon: bool) =>
  mainPlayerWon ? "winning-row" : "";

[@react.component]
let make =
    (
      ~results: list(resultWithRatings),
      // This can be removed as soon as ratings are persisted. Ratings will always be shown then.
      ~temp_showRatings: bool=false,
      ~newResults: option(list(result))=?,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
    ) => {
  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  <>
    <Paper style=containerStyle>
      <Table style=containerStyle size="small">
        <TableHead>
          <TableRow>
            <TableCell style=headToHeadStyle> {text("H2H")} </TableCell>
            <TableCell align="right"> {text("Player1")} </TableCell>
            <TableCell style=numberCellStyle> {text("G1")} </TableCell>
            <TableCell style=colonStyle />
            <TableCell style=numberCellStyle> {text("G2")} </TableCell>
            <TableCell> {text("Player2")} </TableCell>
            <TableCell style=extraTimeStyle align="right" title="Extra time">
              {text("E")}
            </TableCell>
            <TableCell style=dateStyle> {text("Date")} </TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {results
           ->Belt.List.map(resultWithRatings => {
               let result = resultWithRatings.result;
               let player1Won = result.player1goals > result.player2goals;
               let player2Won = !player1Won;
               let mainPlayerWon =
                 player1Won
                 && mainPlayerName === Some(result.player1.name)
                 || player2Won
                 && mainPlayerName === Some(result.player2.name);
               let formattedDate = formatDate(result.date);

               <TableRow
                 key={string_of_int(result.id)}
                 className={
                   getHighlightedClassName(newResults, result)
                   ++ " "
                   ++ getWinningLosingRowClassName(mainPlayerWon)
                 }>
                 <TableCell style=headToHeadStyle>
                   <Link
                     url={
                       "/"
                       ++ communityName
                       ++ "/"
                       ++ result.player1.name
                       ++ "/"
                       ++ result.player2.name
                     }>
                     {text("H2H")}
                   </Link>
                 </TableCell>
                 <TableCell style={getPlayerStyle(player1Won)} align="right">
                   <Link
                     url={"/" ++ communityName ++ "/" ++ result.player1.name}
                     style=playerLinkStyle>
                     {text(result.player1.name)}
                   </Link>
                   {temp_showRatings
                      ? <Rating
                          onClick={_ =>
                            showGraphForPlayer(result.player1.name)
                          }
                          ratingBefore={resultWithRatings.player1RatingBefore}
                          ratingAfter={resultWithRatings.player1RatingAfter}
                        />
                      : ReasonReact.null}
                 </TableCell>
                 <TableCell style=numberCellStyle>
                   {text(string_of_int(result.player1goals))}
                 </TableCell>
                 <TableCell style=colonStyle> {text(":")} </TableCell>
                 <TableCell style=numberCellStyle>
                   {text(string_of_int(result.player2goals))}
                 </TableCell>
                 <TableCell style={getPlayerStyle(player2Won)}>
                   <Link
                     url={"/" ++ communityName ++ "/" ++ result.player2.name}
                     style=playerLinkStyle>
                     {text(result.player2.name)}
                   </Link>
                   {temp_showRatings
                      ? <Rating
                          onClick={_ =>
                            showGraphForPlayer(result.player2.name)
                          }
                          ratingBefore={resultWithRatings.player2RatingBefore}
                          ratingAfter={resultWithRatings.player2RatingAfter}
                        />
                      : ReasonReact.null}
                 </TableCell>
                 <TableCell align="right">
                   {text(result.extratime ? "X" : "")}
                 </TableCell>
                 <TableCell> {text(formattedDate)} </TableCell>
               </TableRow>;
             })
           ->Array.of_list
           ->ReasonReact.array}
        </TableBody>
      </Table>
      {graphIsShownForPlayer->Belt.Option.mapWithDefault(
         ReasonReact.null, playerName =>
         <EloGraphDialog
           isOpen=true
           onClose=hideGraphForPlayer
           playerName
           resultsWithRatings=results
         />
       )}
    </Paper>
  </>;
};
