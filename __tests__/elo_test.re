open Jest;
open Expect;
open EloUtils;
open Streaks_test;

let initialRanking = 1200;
let initialRankings: Belt_MapString.t(int) = Belt_MapString.empty;

type getStreaksTestCase = {
  results: list(testResult),
  expectedRankings: Belt_MapString.t(int),
};

let getStreaksTestCases: list(getStreaksTestCase) = [
  {results: [], expectedRankings: initialRankings},
  {
    results: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1208)
      ->Belt_MapString.set("b", 1192),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
    ],
    expectedRankings: Belt_MapString.empty,
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
      {name1: "a", name2: "b", goals1: 2, goals2: 1},
    ],
    expectedRankings: Belt_MapString.empty,
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
    expectedRankings: Belt_MapString.empty,
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
    expectedRankings: Belt_MapString.empty,
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
    expectedRankings: Belt_MapString.empty,
  },
];

getStreaksTestCases->Belt.List.forEach(testData =>
  describe("getEloRankings", () =>
    test("should return expected rankings", () => {
      let rankings = testData.results |> toTestResults |> getEloRankings;

      expect(rankings) |> toEqual(testData.expectedRankings);
    })
  )
);
