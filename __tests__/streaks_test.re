open Jest;
open Expect;
open Types;
open Utils;

type testScore = {
  name1: string,
  name2: string,
  goals1: int,
  goals2: int,
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

type testStreak = {
  scores: list(testScore),
  endingScore: option(testScore),
};

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

let toResult = (id: int, testScore: testScore) => {
  id,
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

let toTestResults: list(testScore) => list(result) = List.mapi(toResult);
let toTempStreaks: list(testStreak) => list(tempStreak) =
  List.map(s =>
    {
      results: s.scores |> List.mapi(toResult) |> Array.of_list,
      endingResult: s.endingScore->Belt.Option.map(toResult(0)),
    }
  );

let testResults = testData |> toTestResults |> Array.of_list;
let expectedStreaks = expectedTestStreaks |> toTempStreaks |> Array.of_list;

describe("utils", () =>
  describe("getStreaks", () => {
    test("shoulw return true", () => {
      let streaks = testResults |> getAllStreaks;
      expect(streaks) |> toEqual(expectedStreaks);
    });

    test("should return false", () => {
      let qwe = false;

      expect(qwe) |> toBe(false);
    });
  })
);
