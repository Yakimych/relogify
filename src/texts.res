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
  totalPointsWon: string,
  totalPointsLost: string,
  allTimePointDiff: string,
  totalPointsWonPerMatch: string,
  totalPointsLostPerMatch: string,
}

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
  totalPointsWon: "Total goals scored",
  totalPointsLost: "Total goals conceded",
  allTimePointDiff: "All-time goals difference",
  totalPointsWonPerMatch: "Total goals scored per match",
  totalPointsLostPerMatch: "Total goals conceded per match",
}

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
  totalPointsWon: "Total points won",
  totalPointsLost: "Total points lost",
  allTimePointDiff: "All-time point difference",
  totalPointsWonPerMatch: "Total points won per match",
  totalPointsLostPerMatch: "Total points lost per match",
}

let getScoreTypeTexts = a =>
  switch a {
  | #Goals => scoreTypeGoalsTexts
  | #Points => scoreTypePointTexts
  | _ => scoreTypePointTexts
  }
