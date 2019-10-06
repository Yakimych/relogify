open Styles;
open Utils;
open Types;
open Mutations;

type editableResult = {
  id: int,
  player1Id: int,
  player1Goals: int,
  player2Goals: int,
  player2Id: int,
  extraTime: bool,
  date: Js.Date.t,
};

let toEditableResult = (result: result) => {
  id: result.id,
  // TODO: Revisit this typing
  player1Id: result.player1.id,
  player2Id: result.player2.id,
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
  let (isUpdating, setIsUpdating) = React.useState(_ => false);

  let updateResult = () => {
    switch (resultUnderEdit) {
    | Some(resultToUpdate) =>
      Js.log2("Saving: ", resultUnderEdit);
      setIsUpdating(_ => true);
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
      |> Js.Promise.then_(_ => {
           setResultUnderEdit(_ => None);
           setIsUpdating(_ => false) |> Js.Promise.resolve;
         })
      |> Js.Promise.catch(e => {
           Js.Console.error2("Error: ", e);
           setIsUpdating(_ => false) |> Js.Promise.resolve;
         })
      |> ignore;
    | None => ()
    };
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
         ->Belt.List.map(result =>
             <TableRow key={string_of_int(result.id)}>
               <TableCell>
                 {resultUnderEdit->Belt.Option.isNone
                    ? <button
                        onClick={_ =>
                          setResultUnderEdit(_ =>
                            Some(result->toEditableResult)
                          )
                        }>
                        {text("Edit")}
                      </button>
                    : <button onClick={_ => updateResult()}>
                        {text("Save")}
                      </button>}
               </TableCell>
               {resultUnderEdit
                ->Belt.Option.flatMap(r =>
                    r.id == result.id
                      ? Some(
                          <>
                            <TableCell align="right">
                              <ExistingPlayerPicker
                                disabled=isUpdating
                                communityName
                                selectedPlayerId={r.player1Id}
                                onChange={id =>
                                  setResultUnderEdit(_ =>
                                    Some({...r, player1Id: id})
                                  )
                                }
                              />
                            </TableCell>
                            <TableCell style=numberCellStyle>
                              <GoalsPicker
                                disabled=isUpdating
                                selectedGoals={r.player1Goals}
                                onChange={v =>
                                  setResultUnderEdit(_ =>
                                    Some({...r, player1Goals: v})
                                  )
                                }
                              />
                            </TableCell>
                            <TableCell style=colonStyle>
                              {text(":")}
                            </TableCell>
                            <TableCell style=numberCellStyle>
                              <GoalsPicker
                                disabled=isUpdating
                                selectedGoals={r.player2Goals}
                                onChange={v =>
                                  setResultUnderEdit(_ =>
                                    Some({...r, player2Goals: v})
                                  )
                                }
                              />
                            </TableCell>
                            <TableCell>
                              <ExistingPlayerPicker
                                disabled=isUpdating
                                communityName
                                selectedPlayerId={r.player2Id}
                                onChange={id =>
                                  setResultUnderEdit(_ =>
                                    Some({...r, player2Id: id})
                                  )
                                }
                              />
                            </TableCell>
                            <TableCell style=extraTimeStyle align="right">
                              <Checkbox
                                disabled=isUpdating
                                color="default"
                                checked={r.extraTime}
                                onClick={_ =>
                                  setResultUnderEdit(_ =>
                                    Some({...r, extraTime: !r.extraTime})
                                  )
                                }
                              />
                            </TableCell>
                            <TableCell>
                              <TextField
                                disabled=isUpdating
                                _type="date"
                                value={formatDate(r.date)}
                                onChange={e => {
                                  let date =
                                    Js.Date.fromString(
                                      ReactEvent.Form.target(e)##value,
                                    );
                                  if (DateFns.isValid(date)) {
                                    setResultUnderEdit(_ =>
                                      Some({...r, date})
                                    );
                                  };
                                }}
                              />
                            </TableCell>
                          </>,
                        )
                      : None
                  )
                ->Belt.Option.getWithDefault(
                    <>
                      <TableCell align="right">
                        <span> {text(result.player1.name)} </span>
                      </TableCell>
                      <TableCell style=numberCellStyle>
                        {text(string_of_int(result.player1goals))}
                      </TableCell>
                      <TableCell style=colonStyle> {text(":")} </TableCell>
                      <TableCell style=numberCellStyle>
                        {text(string_of_int(result.player2goals))}
                      </TableCell>
                      <TableCell>
                        <span> {text(result.player2.name)} </span>
                      </TableCell>
                      <TableCell style=extraTimeStyle align="right">
                        {text(result.extratime ? "X" : "")}
                      </TableCell>
                      <TableCell>
                        {text(formatDate(result.date))}
                      </TableCell>
                    </>,
                  )}
             </TableRow>
           )
         ->Array.of_list
         ->React.array}
      </TableBody>
    </Table>
  </Paper>;
};
