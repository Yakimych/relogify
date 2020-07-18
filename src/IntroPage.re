open Utils;

[@react.component]
let make = () => {
  <MaterialUi.Paper
    style={ReactDOMRe.Style.make(
      ~margin="24px 16px",
      ~padding="24px 16px",
      ~textAlign="center",
      (),
    )}>
    <MaterialUi.Typography variant=`H4 component={`String("h3")}>
      {text("Welcome to Relogify!")}
    </MaterialUi.Typography>
    <div className="intro-getting-started-container">
      <MaterialUi.Typography component={`String("p")}>
        {text(
           "Save all match results, analyze, view head-to-head records, statistics and more.",
         )}
      </MaterialUi.Typography>
      <RouteLink
        className="button-link create-community-button"
        toPage=CreateCommunityPage>
        <MaterialUi.Button variant=`Contained color=`Primary>
          {text("Create Community")}
        </MaterialUi.Button>
      </RouteLink>
    </div>
    <MaterialUi.Card className="intro-card">
      <MaterialUi.CardContent>
        <MaterialUi.Typography variant=`H6>
          {text("Feature list")}
        </MaterialUi.Typography>
        <MaterialUi.Typography>
          <span> {text("Weekly Results and Leaderboards")} </span>
        </MaterialUi.Typography>
        <MaterialUi.Typography>
          <span> {text("Head-to-Head results and statistics")} </span>
        </MaterialUi.Typography>
        <MaterialUi.Typography>
          <span>
            {text("Individual player results, stats and winning streaks")}
          </span>
        </MaterialUi.Typography>
        <MaterialUi.Typography>
          <span> {text("All-time history and Elo ratings")} </span>
        </MaterialUi.Typography>
      </MaterialUi.CardContent>
    </MaterialUi.Card>
    <MaterialUi.Typography component={`String("p")}>
      <span>
        {text("Found a bug or missing a feature? File an issue in this ")}
      </span>
      <a href="https://github.com/Yakimych/result-log">
        {text("GitHub repo")}
      </a>
      <span> {text(".")} </span>
    </MaterialUi.Typography>
  </MaterialUi.Paper>;
};
