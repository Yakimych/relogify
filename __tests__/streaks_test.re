open Jest;
open Expect;
open Types;
open Streaks;

type testResult = {
  name1: string,
  name2: string,
  goals1: int,
  goals2: int,
};

type testStreak = {
  scores: list(testResult),
  endingScore: option(testResult),
};

type getStreaksTestCase = {
  results: list(testResult),
  expectedStreaks: list(testStreak),
};

let toResult = (testScore: testResult) => {
  id: "0",
  player1: {
    id: "1",
    name: testScore.name1,
  },
  player2: {
    id: "2",
    name: testScore.name2,
  },
  player1goals: testScore.goals1,
  player2goals: testScore.goals2,
  date: Js.Date.fromString("2019-01-01"),
  extratime: false,
};

let toTestResults: list(testResult) => list(matchResult) =
  List.map(toResult);

let toTempStreaks: list(testStreak) => list(streak) =
  List.map(s =>
    {
      results: s.scores |> List.map(toResult) |> Belt.List.reverse,
      endingResult: s.endingScore->Belt.Option.map(toResult),
    }
  );

let getStreaksTestCases: list(getStreaksTestCase) = [
  {results: [], expectedStreaks: []},
  {
    results: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    expectedStreaks: [
      {
        scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
        endingScore: None,
      },
    ],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
    ],
    expectedStreaks: [
      {
        scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
        endingScore: Some({name1: "a", name2: "b", goals1: 1, goals2: 2}),
      },
    ],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
      {name1: "a", name2: "b", goals1: 2, goals2: 1},
    ],
    expectedStreaks: [
      {
        scores: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
        endingScore: Some({name1: "a", name2: "b", goals1: 1, goals2: 2}),
      },
      {
        scores: [{name1: "a", name2: "b", goals1: 2, goals2: 1}],
        endingScore: None,
      },
    ],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 3, goals2: 1},
      {name1: "b", name2: "a", goals1: 1, goals2: 5},
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      // END: Streak1
      {name1: "b", name2: "a", goals1: 1, goals2: 0},
    ],
    expectedStreaks: [
      {
        scores: [
          {name1: "a", name2: "b", goals1: 3, goals2: 0},
          {name1: "a", name2: "b", goals1: 3, goals2: 1},
          {name1: "b", name2: "a", goals1: 1, goals2: 5},
          {name1: "a", name2: "b", goals1: 3, goals2: 0},
        ],
        endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
      },
    ],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 3, goals2: 1},
      {name1: "b", name2: "a", goals1: 1, goals2: 5},
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      // END: Streak1
      {name1: "b", name2: "a", goals1: 1, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
    ],
    expectedStreaks: [
      {
        scores: [
          {name1: "a", name2: "b", goals1: 3, goals2: 0},
          {name1: "a", name2: "b", goals1: 3, goals2: 1},
          {name1: "b", name2: "a", goals1: 1, goals2: 5},
          {name1: "a", name2: "b", goals1: 3, goals2: 0},
        ],
        endingScore: Some({name1: "b", name2: "a", goals1: 1, goals2: 0}),
      },
    ],
  },
  {
    results: [
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
    ],
    expectedStreaks: [
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
    ],
  },
];

getStreaksTestCases->Belt.List.forEach(testData =>
  describe("getStreaks", () =>
    test("should return expected streaks", () => {
      let streaks = testData.results |> toTestResults |> getAllStreaks("a");
      let expectedResult =
        testData.expectedStreaks |> toTempStreaks |> List.rev;

      expect(streaks) |> toEqual(expectedResult);
    })
  )
);
