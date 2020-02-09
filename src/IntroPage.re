open Utils;

[@react.component]
let make = () => {
  <MaterialUi_Paper
    style={ReactDOMRe.Style.make(
      ~margin="24px 16px",
      ~padding="24px 16px",
      ~textAlign="center",
      (),
    )}>
    <Typography variant="h4" component="h3">
      {text("Welcome to Relogify!")}
    </Typography>
    <div className="intro-getting-started-container">
      <Typography component="p">
        {text(
           "Save all match results, analyze, view head-to-head records, statistics and more.",
         )}
      </Typography>
      <RouteLink
        className="button-link create-community-button"
        toPage=CreateCommunityPage>
        <MaterialUi_Button variant=`Contained color=`Primary>
          {ReasonReact.string("Create Community")}
        </MaterialUi_Button>
      </RouteLink>
    </div>
    <MaterialUi_Card className="intro-card">
      <CardContent>
        <Typography variant="h6"> {text("Feature list")} </Typography>
        <Typography>
          <span> {text("Weekly Results and Leaderboards")} </span>
        </Typography>
        <Typography>
          <span> {text("Head-to-Head results and statistics")} </span>
        </Typography>
        <Typography>
          <span>
            {text("Individual player results, stats and winning streaks")}
          </span>
        </Typography>
        <Typography>
          <span> {text("All-time history and Elo ratings")} </span>
        </Typography>
      </CardContent>
    </MaterialUi_Card>
    <Typography component="p">
      <span>
        {text("Found a bug or missing a feature? File an issue in this ")}
      </span>
      <a href="https://github.com/Yakimych/result-log">
        {text("GitHub repo")}
      </a>
      <span> {text(".")} </span>
    </Typography>
  </MaterialUi_Paper>;
};
