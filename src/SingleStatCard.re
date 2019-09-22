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
  <Card className="single-stat-card" raised=true>
    <CardContent>
      <Typography gutterBottom=true> {text(statName)} </Typography>
      <Table size="small">
        <TableBody>
          {playersWithStat
           ->Belt.List.mapWithIndex((i, (name, value)) =>
               <TableRow key={string_of_int(i)}>
                 <TableCell> {i + 1 |> string_of_int |> text} </TableCell>
                 <TableCell align="right"> {text(name)} </TableCell>
                 <TableCell> {text(value)} </TableCell>
               </TableRow>
             )
           ->Belt.List.toArray
           ->React.array}
        </TableBody>
      </Table>
    </CardContent>
  </Card>;
};