open Utils;
open Types;
open Styles;

[@react.component]
let make = (~result) => {
  <>
    <MaterialUi_TableCell align=`Right>
      <span> {text(result.player1.name)} </span>
    </MaterialUi_TableCell>
    <MaterialUi_TableCell style=adminPlayer1PointsCellStyle>
      {text(string_of_int(result.player1goals))}
    </MaterialUi_TableCell>
    <MaterialUi_TableCell style=colonStyle>
      {text(":")}
    </MaterialUi_TableCell>
    <MaterialUi_TableCell style=numberCellStyle>
      {text(string_of_int(result.player2goals))}
    </MaterialUi_TableCell>
    <MaterialUi_TableCell>
      <span> {text(result.player2.name)} </span>
    </MaterialUi_TableCell>
    <MaterialUi_TableCell style=extraTimeStyle align=`Right>
      {text(result.extratime ? "X" : "")}
    </MaterialUi_TableCell>
    <MaterialUi_TableCell>
      {text(formatDate(result.date))}
    </MaterialUi_TableCell>
  </>;
};
