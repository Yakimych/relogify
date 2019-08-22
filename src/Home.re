open Utils /* <Paper className={classes.root}> */;
// const useStyles = makeStyles((theme: Theme) =>
//   createStyles({
//     root: {
//       padding: theme.spacing(3, 2)
//     }
//   })
// );

[@react.component]
let make = () => {
  <div>
    <Paper>
      <Typography variant="h5" component="h3">
        {text("Welcome to ResultLog")}
      </Typography>
      <Typography component="p">
        {text(
           "Save all match results in order to analyze, view head-to-head records, analyze stats and more.",
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
    </Paper>
  </div>;
};
