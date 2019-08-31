open Utils;

[@react.component]
let make = () => {
  <Paper style={ReactDOMRe.Style.make(~padding="24px 16px", ())}>
    <Typography variant="h5" component="h3">
      {text("Welcome to ResultLog")}
    </Typography>
    <Typography component="p">
      {text(
         "Save all match results in order to analyze, view head-to-head records, stats and more.",
       )}
    </Typography>
    <Typography component="p">
      <span>
        {text("Found a bug or missing a feature? File an issue in the ")}
      </span>
      <a href="https://github.com/Yakimych/result-log">
        {text("GitHub repo")}
      </a>
      <span> {text(".")} </span>
    </Typography>
  </Paper>;
};
