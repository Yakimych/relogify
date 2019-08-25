open Jest;
open Expect;
open EloUtils;
open Streaks_test;

type getStreaksTestCase = {
  results: list(testResult),
  expectedRankings: Belt_MapString.t(int),
};

let getStreaksTestCases: list(getStreaksTestCase) = [
  {results: [], expectedRankings: initialRankings},
  {
    results: [{name1: "a", name2: "b", goals1: 0, goals2: 0}],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1200)
      ->Belt_MapString.set("b", 1200),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 0, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 1},
      {name1: "a", name2: "b", goals1: 2, goals2: 2},
      {name1: "a", name2: "b", goals1: 3, goals2: 3},
      {name1: "a", name2: "b", goals1: 4, goals2: 4},
      {name1: "a", name2: "b", goals1: 5, goals2: 5},
      {name1: "a", name2: "b", goals1: 6, goals2: 6},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1200)
      ->Belt_MapString.set("b", 1200),
  },
  {
    results: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1216)
      ->Belt_MapString.set("b", 1184),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1230)
      ->Belt_MapString.set("b", 1170),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1211)
      ->Belt_MapString.set("b", 1189),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 1, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
      {name1: "a", name2: "b", goals1: 0, goals2: 0},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1210)
      ->Belt_MapString.set("b", 1190),
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
