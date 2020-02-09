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
  <MaterialUi_Card raised=true>
    <MaterialUi_CardContent>
      <Typography gutterBottom=true> {text(statName)} </Typography>
      <MaterialUi_Table size=`Small>
        <MaterialUi_TableBody>
          {playersWithStat
           ->Belt.List.mapWithIndex((i, (name, value)) =>
               <MaterialUi_TableRow key={string_of_int(i)}>
                 <MaterialUi_TableCell>
                   {i + 1 |> string_of_int |> text}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell align=`Right>
                   {text(name)}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell> {text(value)} </MaterialUi_TableCell>
               </MaterialUi_TableRow>
             )
           ->Belt.List.toArray
           ->React.array}
        </MaterialUi_TableBody>
      </MaterialUi_Table>
    </MaterialUi_CardContent>
  </MaterialUi_Card>;
};
