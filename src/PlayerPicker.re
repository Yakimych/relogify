open Utils;
open Queries;
open ApolloHooks;

let newPlayerValue = "NEW_PLAYER";

[@react.component]
let make =
    (
      ~communityName: string,
      ~selectedPlayerName: option(string),
      ~disabled: bool,
      ~placeholderText: option(string)=?,
      ~onChange: string => unit,
      ~allowNewPlayer: bool=true,
    ) => {
  let (playersQuery, _) =
    useQuery(
      ~variables=AllPlayersQuery.makeVariables(~communityName, ()),
      AllPlayersQuery.definition,
    );

  let (isInCustomMode, setIsInCustomMode) = React.useState(_ => false);

  let handleSelectChange = (value: string) =>
    if (value === newPlayerValue) {
      onChange("");
      setIsInCustomMode(_ => true);
    } else {
      onChange(value);
    };

  React.useEffect1(
    _ => {
      if (selectedPlayerName->Belt.Option.isNone) {
        setIsInCustomMode(_ => false);
      };
      None;
    },
    [|selectedPlayerName|],
  );

  switch (playersQuery) {
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    let playerNames = data##players->Belt.Array.map(p => p##name);

    isInCustomMode || Belt.Array.length(playerNames) === 0
      ? <TextField
          disabled
          className="highlighted"
          autoFocus=true
          style={ReactDOMRe.Style.make(~width="200px", ())}
          variant="outlined"
          inputProps={"maxLength": 20}
          value={selectedPlayerName->Belt.Option.getWithDefault("")}
          onChange={e => {
            let newName = ReactEvent.Form.target(e)##value;
            onChange(newName);
          }}
        />
      : <MaterialUi_NativeSelect
          disabled
          style={ReactDOMRe.Style.make(~width="200px", ())}
          onChange={e => {
            let newName = ReactEvent.Form.target(e)##value;
            handleSelectChange(newName);
          }}
          value={selectedPlayerName->Belt.Option.getWithDefault("")}
          input={
            <MaterialUi_OutlinedInput
              style={ReactDOMRe.Style.make(~width="60px", ())}
              labelWidth={`Int(0)}
            />
          }>
          <option key="empty" value="" disabled=true>
            {text(placeholderText->Belt.Option.getWithDefault(""))}
          </option>
          {playerNames
           ->Belt.Array.map(p =>
               <option value=p key={"players_" ++ p}> {text(p)} </option>
             )
           ->React.array}
          {allowNewPlayer
             ? <option key="new_player" value=newPlayerValue>
                 {text("+ Add new player")}
               </option>
             : React.null}
        </MaterialUi_NativeSelect>;
  };
};
