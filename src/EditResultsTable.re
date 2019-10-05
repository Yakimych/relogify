open Styles;
open Utils;
open Types;
open Mutations;

type editableResult = {
  id: int,
  player1Id: int,
  player1Name: string,
  player1Goals: int,
  player2Goals: int,
  player2Id: int,
  player2Name: string,
  extraTime: bool,
  date: Js.Date.t,
};

let toEditableResult = (result: result) => {
  id: result.id,
  // TODO: Revisit this typing
  // do we even need the names here?
  player1Id: result.player1.id,
  player2Id: result.player2.id,
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
  let (updateResultMutation, _, _) = UpdateResultMutation.use();
  let (resultUnderEdit, setResultUnderEdit) = React.useState(_ => None);

  let updateResult = resultToUpdate => {
    // TODO: Loading state?
    updateResultMutation(
      ~variables=
        UpdateResultMutationConfig.make(
          ~resultId=resultToUpdate.id,
          ~player1Id=resultToUpdate.player1Id,
          ~player2Id=resultToUpdate.player2Id,
          ~player1Goals=resultToUpdate.player1Goals,
          ~player2Goals=resultToUpdate.player2Goals,
          ~extraTime=resultToUpdate.extraTime,
          (),
        )##variables,
      (),
    )
    |> Js.Promise.then_(_ =>
         setResultUnderEdit(_ => None) |> Js.Promise.resolve
       )  // TODO: Loading state?
    |> Js.Promise.catch(e =>
         Js.Console.error2("Error: ", e) |> Js.Promise.resolve
       )
    |> ignore;
  };

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
                 <button
                   onClick={_ =>
                     resultUnderEdit->Belt.Option.map(updateResult) |> ignore
                   }>
                   {text("Save")}
                 </button>
               </TableCell>
               <TableCell align="right">
                 {resultUnderEdit
                  ->Belt.Option.flatMap(r =>
                      r.id == result.id
                        ? Some(
                            <PlayerPicker
                              // TODO: isUpdating?
                              disabled=false
                              allowNewPlayer=false
                              communityName
                              selectedPlayerName={Some(r.player1Name)}
                              onChange={v =>
                                setResultUnderEdit(_ =>
                                  Some({...r, player1Name: v})
                                )
                              }
                            />,
                          )
                        : None
                    )
                  ->Belt.Option.getWithDefault(
                      <span> {text(result.player1.name)} </span>,
                    )}
               </TableCell>
               <TableCell style=numberCellStyle>
                 {resultUnderEdit
                  ->Belt.Option.flatMap(r =>
                      r.id == result.id
                        ? Some(
                            <GoalsPicker
                              disabled=false
                              selectedGoals={r.player1Goals}
                              onChange={v =>
                                setResultUnderEdit(_ =>
                                  Some({...r, player1Goals: v})
                                )
                              }
                            />,
                          )
                        : None
                    )
                  ->Belt.Option.getWithDefault(
                      text(string_of_int(result.player1goals)),
                    )}
               </TableCell>
               <TableCell style=colonStyle> {text(":")} </TableCell>
               <TableCell style=numberCellStyle>
                 {resultUnderEdit
                  ->Belt.Option.flatMap(r =>
                      r.id == result.id
                        ? Some(
                            <GoalsPicker
                              disabled=false
                              selectedGoals={r.player2Goals}
                              onChange={v =>
                                setResultUnderEdit(_ =>
                                  Some({...r, player2Goals: v})
                                )
                              }
                            />,
                          )
                        : None
                    )
                  ->Belt.Option.getWithDefault(
                      text(string_of_int(result.player2goals)),
                    )}
               </TableCell>
               <TableCell>
                 {resultUnderEdit
                  ->Belt.Option.flatMap(r =>
                      r.id == result.id
                        ? Some(
                            <PlayerPicker
                              // TODO: isUpdating?
                              disabled=false
                              allowNewPlayer=false
                              communityName
                              selectedPlayerName={Some(r.player2Name)}
                              onChange={v =>
                                setResultUnderEdit(_ =>
                                  Some({...r, player2Name: v})
                                )
                              }
                            />,
                          )
                        : None
                    )
                  ->Belt.Option.getWithDefault(
                      <span> {text(result.player2.name)} </span>,
                    )}
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
