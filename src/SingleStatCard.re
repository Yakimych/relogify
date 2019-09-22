open Utils;

let numberCellStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

[@react.component]
let make =
    (~playersWithStat: list((string, string)), ~statName, ~statHeader) => {
  <Card className="single-stat-card">
    <CardContent>
      <Typography> {text(statName)} </Typography>
      <Table size="small">
        <TableHead>
          <TableRow>
            <TableCell style=numberCellStyle> {text("#")} </TableCell>
            <TableCell align="right"> {text("Player")} </TableCell>
            <TableCell> {text(statHeader)} </TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {playersWithStat
           ->Belt.List.mapWithIndex((i, (name, value)) =>
               <TableRow>
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
