open Utils;

[@react.component]
let make = (~title) => {
  let weeklyWinPercentage = [
    ("Player1", "100%"),
    ("Player2", "67%"),
    ("Player3", "43%"),
    ("Player4", "40%"),
    ("Player5", "35%"),
  ];

  let weeklyGoalsScoredPerMatch = [
    ("Player1", "1.1"),
    ("Player2", "2.1"),
    ("Player3", "3.3"),
    ("Player4", "3.4"),
    ("Player5", "5.0"),
  ];

  let weeklyEloDifference = [
    ("Player1", "+56"),
    ("Player2", "+16"),
    ("Player3", "+2"),
    ("Player4", "-10"),
    ("Player5", "-120"),
  ];

  <>
    <Paper>
      <div className="title">
        <Typography variant="h6"> {text(title)} </Typography>
      </div>
      <div className="top-stats-container">
        <SingleStatCard
          playersWithStat=weeklyWinPercentage
          statName="Win Percentage"
          statHeader="Win %"
        />
        <SingleStatCard
          playersWithStat=weeklyGoalsScoredPerMatch
          statName="Goals Scored per Match"
          statHeader="G/M"
        />
        <SingleStatCard
          playersWithStat=weeklyGoalsScoredPerMatch
          statName="Goals Conceded per Match"
          statHeader="GC/M"
        />
        <SingleStatCard
          playersWithStat=weeklyEloDifference
          statName="Elo Difference"
          statHeader="+/-"
        />
      </div>
    </Paper>
  </>;
};
