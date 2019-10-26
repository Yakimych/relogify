type scoreTypeTexts = {
  morePoints: string,
  pointsWon: string,
  pointsWonShort: string,
  pointsLost: string,
  pointsLostShort: string,
  pointDiff: string,
  pointsWonPerMatch: string,
  pointsWonPerMatchShort: string,
  pointsLostPerMatch: string,
  pointsLostPerMatchShort: string,
  pointsPlayerShort: string,
};

let scoreTypeGoalsTexts = {
  morePoints: "More goals",
  pointsWon: "Goals scored",
  pointsWonShort: "GS",
  pointsLost: "Goals conceded",
  pointsLostShort: "GC",
  pointDiff: "Goal difference",
  pointsWonPerMatch: "Goals scored per match",
  pointsWonPerMatchShort: "G/M",
  pointsLostPerMatch: "Goals conceded per match",
  pointsLostPerMatchShort: "C/M",
  pointsPlayerShort: "G",
};

let scoreTypePointTexts = {
  morePoints: "More points",
  pointsWon: "Points won",
  pointsWonShort: "PW",
  pointsLost: "Points lost",
  pointsLostShort: "PL",
  pointDiff: "Point difference",
  pointsWonPerMatch: "Points won per match",
  pointsWonPerMatchShort: "P/M",
  pointsLostPerMatch: "Points lost per match",
  pointsLostPerMatchShort: "L/M",
  pointsPlayerShort: "P",
};

let getScoreTypeTexts =
  fun
  | `Goals => scoreTypeGoalsTexts
  | `Points => scoreTypePointTexts;
