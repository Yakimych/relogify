open Jest;
open Expect;
open Types;
open Utils;

// TODO: Better type names
type testScore = {
  name1: string,
  name2: string,
  goals1: int,
  goals2: int,
};

type testStreak = {
  scores: list(testScore),
  endingScore: option(testScore),
};

let testData: list(testScore) = [
  // START: Streak1
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  {name1: "a", name2: "b", goals1: 3, goals2: 1},
  {name1: "b", name2: "a", goals1: 1, goals2: 5},
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  // END: Streak1
  {name1: "b", name2: "a", goals1: 1, goals2: 0},
  {name1: "a", name2: "b", goals1: 1, goals2: 2},
  // START: Streak2
  {name1: "b", name2: "a", goals1: 0, goals2: 4},
  {name1: "a", name2: "b", goals1: 1, goals2: 0},
  // END: Streak2
  {name1: "b", name2: "a", goals1: 1, goals2: 0},
  {name1: "b", name2: "a", goals1: 4, goals2: 0},
  // START: Streak3
  {name1: "a", name2: "b", goals1: 1, goals2: 0},
];

let expectedTestStreaks: list(testStreak) = [
  {
    scores: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 3, goals2: 1},
      {name1: "b", name2: "a", goals1: 1, goals2: 5},
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
    ],
    endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
  },
  {
    scores: [
      {name1: "b", name2: "a", goals1: 0, goals2: 4},
      {name1: "a", name2: "b", goals1: 1, goals2: 0},
    ],
    endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
  },
  {
    scores: [{name1: "a", name2: "b", goals1: 1, goals2: 0}],
    endingScore: None,
  },
];

// TODO: Rewrite with testcases
let testData1: list(testScore) = [
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
];

let testData2: list(testScore) = [
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  {name1: "a", name2: "b", goals1: 1, goals2: 2},
];

let testData3: list(testScore) = [
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  {name1: "a", name2: "b", goals1: 1, goals2: 2},
  {name1: "a", name2: "b", goals1: 2, goals2: 1},
];

let testData4: list(testScore) = [
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  {name1: "a", name2: "b", goals1: 3, goals2: 1},
  {name1: "b", name2: "a", goals1: 1, goals2: 5},
  {name1: "a", name2: "b", goals1: 3, goals2: 0},
  // END: Streak1
  {name1: "b", name2: "a", goals1: 1, goals2: 0},
  {name1: "a", name2: "b", goals1: 1, goals2: 2},
  // // START: Streak2
  // {name1: "b", name2: "a", goals1: 0, goals2: 4},
  // {name1: "a", name2: "b", goals1: 1, goals2: 0},
  // // END: Streak2
  // {name1: "b", name2: "a", goals1: 1, goals2: 0},
  // {name1: "b", name2: "a", goals1: 4, goals2: 0},
  // // START: Streak3
  // {name1: "a", name2: "b", goals1: 1, goals2: 0},
];

let expectedTestStreaks1: list(testStreak) = [
  {
    scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    endingScore: None,
  },
];

let expectedTestStreaks2: list(testStreak) = [
  {
    scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    endingScore: Some({name1: "a", name2: "b", goals1: 1, goals2: 2}),
  },
];

let expectedTestStreaks3: list(testStreak) = [
  {
    scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    endingScore: Some({name1: "a", name2: "b", goals1: 1, goals2: 2}),
  },
  {
    scores: [{name1: "a", name2: "b", goals1: 2, goals2: 1}],
    endingScore: None,
  },
];

let expectedTestStreaks4: list(testStreak) = [
  {
    scores: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 3, goals2: 1},
      {name1: "b", name2: "a", goals1: 1, goals2: 5},
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
    ],
    endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
  },
  // {
  //   scores: [
  //     {name1: "b", name2: "a", goals1: 0, goals2: 4},
  //     {name1: "a", name2: "b", goals1: 1, goals2: 0},
  //   ],
  //   endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
  // },
  // {
  //   scores: [{name1: "a", name2: "b", goals1: 1, goals2: 0}],
  //   endingScore: None,
  // },
];

let toResult = (testScore: testScore) => {
  id: 0,
  player1: {
    name: testScore.name1,
  },
  player2: {
    name: testScore.name2,
  },
  player1goals: testScore.goals1,
  player2goals: testScore.goals2,
  date: "2019-01-01",
  extratime: false,
};

let toTestResults: list(testScore) => list(result) = List.map(toResult);
let toTempStreaks: list(testStreak) => list(tempStreak) =
  List.map(s =>
    {
      results: s.scores |> List.map(toResult) |> Belt.List.reverse,
      endingResult: s.endingScore->Belt.Option.map(toResult),
    }
  );

let testResults = testData |> toTestResults;
let expectedStreaks =
  expectedTestStreaks |> toTempStreaks |> Belt.List.reverse;

let testResults1 = testData1 |> toTestResults;
let expectedStreaks1 =
  expectedTestStreaks1 |> toTempStreaks |> Belt.List.reverse;

let testResults2 = testData2 |> toTestResults;
let expectedStreaks2 =
  expectedTestStreaks2 |> toTempStreaks |> Belt.List.reverse;

let testResults3 = testData3 |> toTestResults;
let expectedStreaks3 =
  expectedTestStreaks3 |> toTempStreaks |> Belt.List.reverse;

let testResults4 = testData4 |> toTestResults;
let expectedStreaks4 =
  expectedTestStreaks4 |> toTempStreaks |> Belt.List.reverse;

describe("utils", () =>
  describe("getStreaks", () => {
    // TODO: Better names for tests
    test("should return 3 streaks", () => {
      let streaks = testResults |> getAllStreaks("a");
      expect(streaks) |> toEqual(expectedStreaks);
    });

    test("test", () => {
      let streaks = testResults4 |> getAllStreaks("a");
      expect(streaks) |> toEqual(expectedStreaks4);
    });

    test("should return 2 streaks testcase_3", () => {
      let streaks = testResults3 |> getAllStreaks("a");
      expect(streaks) |> toEqual(expectedStreaks3);
    });

    test("should return 0 streaks for empty inputs", () => {
      let streaks = [] |> getAllStreaks("a");
      expect(streaks) |> toEqual([]);
    });

    test("should return 1 streak with no ending result for a single entry", () => {
      let streaks = testResults1 |> getAllStreaks("a");
      expect(streaks) |> toEqual(expectedStreaks1);
    });

    test("should return 1 streak with ending result for two entries", () => {
      let streaks = testResults2 |> getAllStreaks("a");
      expect(streaks) |> toEqual(expectedStreaks2);
    });
  })
);
