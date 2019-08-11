let goalValues = Belt.Array.range(0, 9);
let moreGoalsValue = "MORE_GOALS";

[@react.component]
let make = (~selectedGoals: int, ~disabled: bool, ~onChange) => {
  let (isInCustomMode, setIsInCustomMode) = React.useState(() => false);

  let handleSelectChange = (value: string) =>
    if (value == moreGoalsValue) {
      setIsInCustomMode(_ => true);
    } else {
      onChange(int_of_string(value));
    };

  <>
    {isInCustomMode
       ? <TextField
           disabled
           className="highlighted"
           autoFocus=true
           type_="number"
           style={ReactDOMRe.Style.make(~width="80px", ())}
           variant="outlined"
           value={string_of_int(selectedGoals)}
           // TODO: validNumberOfGoals
           onChange={e => onChange(ReactEvent.Form.target(e)##value)}
         />
       : <span>
           <NativeSelect
             disabled
             value={string_of_int(selectedGoals)}
             onChange={e =>
               handleSelectChange(ReactEvent.Form.target(e)##value)
             }
             input={
               <OutlinedInput
                 labelWidth=0
                 style={ReactDOMRe.Style.make(~width="60px", ())}
               />
             }>
             {goalValues
              ->Belt.Array.map(g =>
                  <option
                    key={"goals_" ++ string_of_int(g)}
                    value={string_of_int(g)}>
                    {ReasonReact.string(string_of_int(g))}
                  </option>
                )
              ->ReasonReact.array}
             <option key="more_goals" value=moreGoalsValue>
               {ReasonReact.string("More goals!")}
             </option>
           </NativeSelect>
         </span>}
  </>;
};
