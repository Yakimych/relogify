[@react.component]
let make = () => {
  let (isAddingResult, setIsAddingResult) = React.useState(() => false);
  let (goals1, setGoals1) = React.useState(() => 0);
  let (goals2, setGoals2) = React.useState(() => 0);

  <>
    <Paper
      style={ReactDOMRe.Style.make(~width="550px", ~marginBottom="30px", ())}>
      <div style={ReactDOMRe.Style.make(~display="flex", ())}>
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals1
          onChange={v => setGoals1(_ => v)}
        />
        <GoalsPicker
          disabled=isAddingResult
          selectedGoals=goals2
          onChange={v => setGoals2(_ => v)}
        />
      </div>
    </Paper>
  </>;
};
