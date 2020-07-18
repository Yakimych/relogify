open Utils;
open Types;
open Styles;

[@react.component]
let make = (~result) => {
  <>
    <MaterialUi.TableCell align=`Right>
      <span> {text(result.player1.name)} </span>
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=adminPlayer1PointsCellStyle>
      {text(string_of_int(result.player1goals))}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=colonStyle>
      {text(":")}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      {text(string_of_int(result.player2goals))}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      <span> {text(result.player2.name)} </span>
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=extraTimeStyle align=`Right>
      {text(result.extratime ? "X" : "")}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell>
      {text(formatDate(result.date))}
    </MaterialUi.TableCell>
  </>;
};
