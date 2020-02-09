open Utils;

let moreGoalsValue = "MORE_GOALS";

[@react.component]
let make =
    (
      ~selectedGoals: int,
      ~disabled: bool,
      ~onChange,
      ~scoreType,
      ~maxSelectablePoints: int,
    ) => {
  let scoreTypeTexts = Texts.getScoreTypeTexts(scoreType);
  let (isInCustomMode, setIsInCustomMode) = React.useState(_ => false);
  let goalValues = Belt.Array.range(0, maxSelectablePoints);

  let handleSelectChange = (value: string) =>
    if (value === moreGoalsValue) {
      setIsInCustomMode(_ => true);
    } else {
      onChange(int_of_string(value));
    };

  let isWide = MaterialUi.useMediaQuery("(min-width: 600px)");
  <>
    {isInCustomMode
       ? <TextField
           disabled
           className="highlighted"
           autoFocus=true
           _type="number"
           style={ReactDOMRe.Style.make(~width=isWide ? "100px" : "80px", ())}
           variant="outlined"
           value={string_of_int(selectedGoals)}
           onChange={e => {
             let newGoalsValue =
               ReactEvent.Form.target(e)##value |> validNumberOfGoals;
             onChange(newGoalsValue);
           }}
         />
       : <span>
           <MaterialUi_NativeSelect
             disabled
             value={string_of_int(selectedGoals)}
             onChange={e => {
               let newGoalsValue = ReactEvent.Form.target(e)##value;
               handleSelectChange(newGoalsValue);
             }}
             input={
               <MaterialUi_OutlinedInput
                 labelWidth={`Int(0)}
                 style={ReactDOMRe.Style.make(
                   ~width=isWide ? "64px" : "60px",
                   (),
                 )}
               />
             }>
             {goalValues
              ->Belt.Array.map(g =>
                  <option
                    key={"goals_" ++ string_of_int(g)}
                    value={string_of_int(g)}>
                    {text(string_of_int(g))}
                  </option>
                )
              ->React.array}
             <option key="more_goals" value=moreGoalsValue>
               {text(scoreTypeTexts.morePoints)}
             </option>
           </MaterialUi_NativeSelect>
         </span>}
  </>;
};
