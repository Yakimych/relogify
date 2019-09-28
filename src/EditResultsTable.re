open Styles;
open Utils;
open Types;

let colonStyle =
  ReactDOMRe.Style.make(
    ~width="5px",
    ~paddingLeft="0",
    ~paddingRight="0",
    (),
  );

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

let extraTimeStyle = ReactDOMRe.Style.make(~width="20px", ());

[@react.component]
let make = (~results: list(result), ~communityName: string) => {
  <Paper>
    <div className="title">
      <Typography variant="h6"> {text("Results")} </Typography>
    </div>
    <Table size="small">
      <TableHead>
        <TableRow>
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
         ->Belt.List.map(result => {
             let formattedDate = formatDate(result.date);

             <TableRow key={string_of_int(result.id)}>
               <TableCell align="right">
                 <RouteLink
                   toPage={PlayerHome(communityName, result.player1.name)}
                   style=playerLinkStyle>
                   {text(result.player1.name)}
                 </RouteLink>
               </TableCell>
               <TableCell style=numberCellStyle>
                 {text(string_of_int(result.player1goals))}
               </TableCell>
               <TableCell style=colonStyle> {text(":")} </TableCell>
               <TableCell style=numberCellStyle>
                 {text(string_of_int(result.player2goals))}
               </TableCell>
               <TableCell>
                 <RouteLink
                   toPage={PlayerHome(communityName, result.player2.name)}
                   style=playerLinkStyle>
                   {text(result.player2.name)}
                 </RouteLink>
               </TableCell>
               <TableCell style=extraTimeStyle align="right">
                 {text(result.extratime ? "X" : "")}
               </TableCell>
               <TableCell> {text(formattedDate)} </TableCell>
             </TableRow>;
           })
         ->Array.of_list
         ->React.array}
      </TableBody>
    </Table>
  </Paper>;
};
