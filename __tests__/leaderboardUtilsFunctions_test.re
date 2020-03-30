open Jest;
open Expect;
open Types;
open LeaderboardUtils;

describe("leaderboardFunctions", () => {
  let singleDrawResult = {
    id: 0,
    player1: {
      id: 1,
      name: "Bob",
    },
    player2: {
      id: 2,
      name: "Alice",
    },
    player1goals: 1,
    player2goals: 1,
    extratime: false,
    date: Js.Date.fromString("2019-07-27T07:26:31.667+00:00"),
  };

  let expectedLeaderboardForSingleDraw = [
    {
      playerName: "Alice",
      matchesWon: 0,
      matchesLost: 0,
      matchesDrawn: 1,
      goalsScored: 1,
      goalsConceded: 1,
    },
    {
      playerName: "Bob",
      matchesWon: 0,
      matchesLost: 0,
      matchesDrawn: 1,
      goalsScored: 1,
      goalsConceded: 1,
    },
  ];

  test("should return leaderboard with two entries for single draw", () => {
    let leaderboard =
      getLeaderboard([singleDrawResult]) |> List.sort(byName);
    expect(leaderboard)
    |> toEqual(expectedLeaderboardForSingleDraw |> List.sort(byName));
  });

  test("pointsPerMatch should be 1 for single 1:1 draw result", () => {
    let singleLeaderboardRow = getLeaderboard([singleDrawResult]) |> List.hd;

    let pointsPerMatch = goalsScoredPerMatch(singleLeaderboardRow);
    expect(pointsPerMatch) |> toEqual(1.0);
  });

  test("pointsConcededPerMatch should be 1 for single 1:1 draw result", () => {
    let singleLeaderboardRow = getLeaderboard([singleDrawResult]) |> List.hd;

    let pointsConcededPerMatch = goalsConcededPerMatch(singleLeaderboardRow);
    expect(pointsConcededPerMatch) |> toEqual(1.0);
  });
});
