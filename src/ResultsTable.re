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
      ~newResults: option(list(result))=?,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
    ) =>
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
               let r = resultWithRatings.result;
               let player1Won = r.player1goals > r.player2goals;
               let player2Won = !player1Won;
               let mainPlayerWon =
                 player1Won
                 && mainPlayerName === Some(r.player1.name)
                 || player2Won
                 && mainPlayerName === Some(r.player2.name);
               let formattedDate = formatDate(r.date);

               <TableRow
                 key={string_of_int(r.id)}
                 className={
                   getHighlightedClassName(newResults, r)
                   ++ " "
                   ++ getWinningLosingRowClassName(mainPlayerWon)
                 }>
                 <TableCell style=headToHeadStyle>
                   <Link
                     url={
                       "/"
                       ++ communityName
                       ++ "/"
                       ++ r.player1.name
                       ++ "/"
                       ++ r.player2.name
                     }>
                     {text("H2H")}
                   </Link>
                 </TableCell>
                 <TableCell style={getPlayerStyle(player1Won)} align="right">
                   <Link
                     url={"/" ++ communityName ++ "/" ++ r.player1.name}
                     style=playerLinkStyle>
                     {text(r.player1.name)}
                   </Link>
                   <Rating
                     ratingBefore={resultWithRatings.player1RatingBefore}
                     ratingAfter={resultWithRatings.player1RatingAfter}
                   />
                 </TableCell>
                 <TableCell style=numberCellStyle>
                   {text(string_of_int(r.player1goals))}
                 </TableCell>
                 <TableCell style=colonStyle> {text(":")} </TableCell>
                 <TableCell style=numberCellStyle>
                   {text(string_of_int(r.player2goals))}
                 </TableCell>
                 <TableCell style={getPlayerStyle(player2Won)}>
                   <Link
                     url={"/" ++ communityName ++ "/" ++ r.player2.name}
                     style=playerLinkStyle>
                     {text(r.player2.name)}
                   </Link>
                   <Rating
                     ratingBefore={resultWithRatings.player2RatingBefore}
                     ratingAfter={resultWithRatings.player2RatingAfter}
                   />
                 </TableCell>
                 <TableCell align="right">
                   {text(r.extratime ? "X" : "")}
                 </TableCell>
                 <TableCell> {text(formattedDate)} </TableCell>
               </TableRow>;
             })
           ->Array.of_list
           ->ReasonReact.array}
        </TableBody>
      </Table>
    </Paper>
  </>;
