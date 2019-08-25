open Jest;
open Expect;
open EloUtils;
open Streaks_test;

type getStreaksTestCase = {
  results: list(testResult),
  expectedRankings: list((string, float)),
};

let getStreaksTestCases: list(getStreaksTestCase) = [
  {results: [], expectedRankings: initialRatings |> Belt_MapString.toList},
  {
    results: [{name1: "a", name2: "b", goals1: 0, goals2: 0}],
    expectedRankings: [("a", 1200.0), ("b", 1200.0)],
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
    expectedRankings: [("a", 1200.0), ("b", 1200.0)],
  },
  {
    results: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    expectedRankings: [("a", 1216.0), ("b", 1184.0)],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
    ],
    expectedRankings: [("a", 1231.0), ("b", 1169.0)],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
    ],
    expectedRankings: [("a", 1212.0), ("b", 1188.0)],
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
      {name1: "a", name2: "b", goals1: 0, goals2: 0},
    ],
    expectedRankings: [("a", 1211.0), ("b", 1189.0)],
  },
];

getStreaksTestCases->Belt.List.forEach(testData =>
  describe("getEloRankings", () =>
    test("should return expected rankings", () => {
      let rankings =
        testData.results
        ->toTestResults
        ->getEloRankings
        ->Belt.List.map(((k, v)) => (k, Js.Math.round(v)));

      expect(rankings) |> toEqual(testData.expectedRankings);
    })
  )
);
