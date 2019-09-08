open Utils;

let newPlayerValue = "NEW_PLAYER";

[@react.component]
let make =
    (
      ~playerNames: array(string),
      ~selectedPlayerName: option(string),
      ~disabled: bool,
      ~placeholderText: option(string)=?,
      ~onChange: string => unit,
    ) => {
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

  <>
    {isInCustomMode
       ? <TextField
           disabled
           className="highlighted"
           autoFocus=true
           style={ReactDOMRe.Style.make(~width="200px", ())}
           variant="outlined"
           inputProps={"maxLength": 20}
           value={selectedPlayerName->Belt.Option.getWithDefault("")}
           onChange={e => onChange(ReactEvent.Form.target(e)##value)}
         />
       : <NativeSelect
           disabled
           style={ReactDOMRe.Style.make(~width="200px", ())}
           onChange={e =>
             handleSelectChange(ReactEvent.Form.target(e)##value)
           }
           value={selectedPlayerName->Belt.Option.getWithDefault("")}
           input={
             <OutlinedInput
               style={ReactDOMRe.Style.make(~width="60px", ())}
               labelWidth=0
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
           <option key="new_player" value=newPlayerValue>
             {text("+ Add new player")}
           </option>
         </NativeSelect>}
  </>;
};
