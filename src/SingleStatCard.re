open Utils;

let numberCellStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

[@react.component]
let make = (~playersWithStat: list((string, string)), ~statName) => {
  <MaterialUi.Card raised=true>
    <MaterialUi.CardContent>
      <MaterialUi.Typography gutterBottom=true>
        {text(statName)}
      </MaterialUi.Typography>
      <MaterialUi.Table size=`Small>
        <MaterialUi.TableBody>
          {playersWithStat
           ->Belt.List.mapWithIndex((i, (name, value)) =>
               <MaterialUi.TableRow key={string_of_int(i)}>
                 <MaterialUi.TableCell>
                   {i + 1 |> string_of_int |> text}
                 </MaterialUi.TableCell>
                 <MaterialUi.TableCell align=`Right>
                   {text(name)}
                 </MaterialUi.TableCell>
                 <MaterialUi.TableCell> {text(value)} </MaterialUi.TableCell>
               </MaterialUi.TableRow>
             )
           ->Belt.List.toArray
           ->React.array}
        </MaterialUi.TableBody>
      </MaterialUi.Table>
    </MaterialUi.CardContent>
  </MaterialUi.Card>;
};
