open Utils;
open Types;
open Styles;

[@react.component]
let make = (~result) => {
  <>
    <TableCell align="right">
      <span> {text(result.player1.name)} </span>
    </TableCell>
    <TableCell style=adminPlayer1PointsCellStyle>
      {text(string_of_int(result.player1goals))}
    </TableCell>
    <TableCell style=colonStyle> {text(":")} </TableCell>
    <TableCell style=numberCellStyle>
      {text(string_of_int(result.player2goals))}
    </TableCell>
    <TableCell> <span> {text(result.player2.name)} </span> </TableCell>
    <TableCell style=extraTimeStyle align="right">
      {text(result.extratime ? "X" : "")}
    </TableCell>
    <TableCell> {text(formatDate(result.date))} </TableCell>
  </>;
};
