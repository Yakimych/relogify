open Styles;

type player = {name: string};
type result = {
  id: int,
  player1: player,
  player2: player,
  player1goals: int,
  player2goals: int,
  date: string,
  extratime: bool,
};

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

let text = ReasonReact.string;

[@react.component]
let make =
    (
      ~results: array(result),
      ~newResults: option(array(result))=?,
      ~communityName: string,
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
           ->Belt.Array.map(r => {
               let player1Won = r.player1goals > r.player2goals;
               let player2Won = !player1Won;
               // TODO: Fix date formatting
               //  let formattedDate = formatDate(new Date(r.date));
               let formattedDate = "2019-01-02";

               let resultIsFresh =
                 newResults
                 ->Belt.Option.map(n => n->Belt.Array.some(nr => nr == r))
                 ->Belt.Option.getWithDefault(false);
               let newResultsClassName = resultIsFresh ? "highlighted" : "";

               <TableRow
                 key={string_of_int(r.id)} className=newResultsClassName>
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
                 </TableCell>
                 <TableCell align="right">
                   {text(r.extratime ? "X" : "")}
                 </TableCell>
                 <TableCell> {text(formattedDate)} </TableCell>
               </TableRow>;
             })
           ->ReasonReact.array}
        </TableBody>
      </Table>
    </Paper>
  </>;
