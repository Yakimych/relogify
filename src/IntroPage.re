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
    <MaterialUi_Typography variant=`H4 component={`String("h3")}>
      {text("Welcome to Relogify!")}
    </MaterialUi_Typography>
    <div className="intro-getting-started-container">
      <MaterialUi_Typography component={`String("p")}>
        {text(
           "Save all match results, analyze, view head-to-head records, statistics and more.",
         )}
      </MaterialUi_Typography>
      <RouteLink
        className="button-link create-community-button"
        toPage=CreateCommunityPage>
        <MaterialUi_Button variant=`Contained color=`Primary>
          {text("Create Community")}
        </MaterialUi_Button>
      </RouteLink>
    </div>
    <MaterialUi_Card className="intro-card">
      <MaterialUi_CardContent>
        <MaterialUi_Typography variant=`H6>
          {text("Feature list")}
        </MaterialUi_Typography>
        <MaterialUi_Typography>
          <span> {text("Weekly Results and Leaderboards")} </span>
        </MaterialUi_Typography>
        <MaterialUi_Typography>
          <span> {text("Head-to-Head results and statistics")} </span>
        </MaterialUi_Typography>
        <MaterialUi_Typography>
          <span>
            {text("Individual player results, stats and winning streaks")}
          </span>
        </MaterialUi_Typography>
        <MaterialUi_Typography>
          <span> {text("All-time history and Elo ratings")} </span>
        </MaterialUi_Typography>
      </MaterialUi_CardContent>
    </MaterialUi_Card>
    <MaterialUi_Typography component={`String("p")}>
      <span>
        {text("Found a bug or missing a feature? File an issue in this ")}
      </span>
      <a href="https://github.com/Yakimych/result-log">
        {text("GitHub repo")}
      </a>
      <span> {text(".")} </span>
    </MaterialUi_Typography>
  </MaterialUi_Paper>;
};
