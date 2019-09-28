open Styles;
open Utils;
open Types;

type editableResult = {
  id: int,
  player1Name: string,
  player1Goals: int,
  player2Goals: int,
  player2Name: string,
  extraTime: bool,
  date: Js.Date.t,
};

let toEditableResult = (result: result) => {
  id: result.id,
  player1Name: result.player1.name,
  player2Name: result.player2.name,
  player1Goals: result.player1goals,
  player2Goals: result.player2goals,
  extraTime: result.extratime,
  date: result.date,
};

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
  let (resultUnderEdit, setResultUnderEdit) = React.useState(_ => None);

  <Paper>
    <div className="title">
      <Typography variant="h6"> {text("Results")} </Typography>
    </div>
    <Table size="small">
      <TableHead>
        <TableRow>
          <TableCell> {text("Edit")} </TableCell>
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
             let editableResult = result |> toEditableResult;

             <TableRow key={string_of_int(result.id)}>
               <TableCell>
                 <button
                   onClick={_ =>
                     setResultUnderEdit(_ => Some(editableResult))
                   }>
                   {text("Edit")}
                 </button>
                 <button onClick={_ => setResultUnderEdit(_ => None)}>
                   {text("Save")}
                 </button>
               </TableCell>
               <TableCell align="right">
                 {resultUnderEdit->Belt.Option.mapWithDefault(false, r =>
                    r.id == result.id
                  )
                    ? <input
                        type_="text"
                        onChange={e => {
                          let newValue = ReactEvent.Form.target(e)##value;
                          setResultUnderEdit(maybeOldResult =>
                            maybeOldResult->Belt.Option.map(oldResult =>
                              {...oldResult, player1Name: newValue}
                            )
                          );
                        }}
                        value={
                                Belt.Option.getExn(resultUnderEdit).player1Name
                              }
                      />
                    : <RouteLink
                        toPage={
                          PlayerHome(communityName, result.player1.name)
                        }
                        style=playerLinkStyle>
                        {text(result.player1.name)}
                      </RouteLink>}
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
