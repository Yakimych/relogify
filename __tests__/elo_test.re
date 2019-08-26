open Jest;
open Expect;
open EloUtils;
open Streaks_test;

type getStreaksTestCase = {
  results: list(testResult),
  expectedRankings: eloMap,
};

let getStreaksTestCases: list(getStreaksTestCase) = [
  {results: [], expectedRankings: Belt_MapString.empty},
  {
    results: [{name1: "a", name2: "b", goals1: 0, goals2: 0}],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1200.0)
      ->Belt_MapString.set("b", 1200.0),
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
      ->Belt_MapString.set("a", 1200.0)
      ->Belt_MapString.set("b", 1200.0),
  },
  {
    results: [{name1: "a", name2: "b", goals1: 3, goals2: 0}],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1216.0)
      ->Belt_MapString.set("b", 1184.0),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1231.0)
      ->Belt_MapString.set("b", 1169.0),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1212.0)
      ->Belt_MapString.set("b", 1188.0),
  },
  {
    results: [
      {name1: "a", name2: "b", goals1: 3, goals2: 0},
      {name1: "a", name2: "b", goals1: 5, goals2: 2},
      {name1: "b", name2: "a", goals1: 2, goals2: 1},
      {name1: "a", name2: "b", goals1: 0, goals2: 0},
    ],
    expectedRankings:
      Belt_MapString.empty
      ->Belt_MapString.set("a", 1211.0)
      ->Belt_MapString.set("b", 1189.0),
  },
];

getStreaksTestCases->Belt.List.forEach(testData =>
  describe("getEloRankings", () =>
    test("should return expected rankings", () => {
      let rankings =
        testData.results
        ->toTestResults
        ->getEloRatingMap
        ->Belt_MapString.map(Js.Math.round);

      expect(rankings) |> toEqual(testData.expectedRankings);
    })
  )
);
