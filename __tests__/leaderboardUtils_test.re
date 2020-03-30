open Jest;
open Expect;
open Types;
open LeaderboardUtils;

let testResults: list(matchResult) = [
  {
    player1: {
      id: 1,
      name: "Qwe",
    },
    player2: {
      id: 2,
      name: "Abc",
    },
    player2goals: 4,
    player1goals: 0,
    extratime: false,
    date: Js.Date.fromString("2019-07-27T07:26:31.667+00:00"),
    id: 116,
  },
  {
    player1: {
      id: 1,
      name: "Qwe",
    },
    player2: {
      id: 2,
      name: "Abc",
    },
    player2goals: 1,
    player1goals: 2,
    extratime: true,
    date: Js.Date.fromString("2019-07-27T07:26:21.42+00:00"),
    id: 115,
  },
  {
    player1: {
      id: 1,
      name: "Qwe",
    },
    player2: {
      id: 2,
      name: "Abc",
    },
    player2goals: 3,
    player1goals: 3,
    extratime: false,
    date: Js.Date.fromString("2019-07-27T07:26:20.42+00:00"),
    id: 115,
  },
  {
    player1: {
      id: 2,
      name: "Abc",
    },
    player2: {
      id: 3,
      name: "Def",
    },
    player2goals: 4,
    player1goals: 6,
    extratime: false,
    date: Js.Date.fromString("2019-07-27T06:29:51.565+00:00"),
    id: 114,
  },
  {
    player1: {
      id: 2,
      name: "Abc",
    },
    player2: {
      id: 1,
      name: "Qwe",
    },
    player2goals: 1,
    player1goals: 3,
    extratime: false,
    date: Js.Date.fromString("2019-07-27T06:29:32.534+00:00"),
    id: 113,
  },
  {
    player1: {
      id: 4,
      name: "Player4",
    },
    player2: {
      id: 5,
      name: "Yet another one",
    },
    player2goals: 12,
    player1goals: 9,
    extratime: false,
    date: Js.Date.fromString("2019-07-23T20:24:02.917+00:00"),
    id: 102,
  },
  {
    player1: {
      id: 6,
      name: "Another new player",
    },
    player2: {
      id: 5,
      name: "Yet another one",
    },
    player2goals: 1,
    player1goals: 4,
    extratime: false,
    date: Js.Date.fromString("2019-07-23T20:12:45.985+00:00"),
    id: 101,
  },
  {
    player1: {
      id: 7,
      name: "NewP1",
    },
    player2: {
      id: 8,
      name: "NewP2",
    },
    player2goals: 1,
    player1goals: 2,
    extratime: true,
    date: Js.Date.fromString("2019-07-23T20:04:19.8+00:00"),
    id: 100,
  },
  {
    player1: {
      id: 4,
      name: "Player4",
    },
    player2: {
      id: 5,
      name: "Yet another one",
    },
    player2goals: 6,
    player1goals: 3,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T20:48:17+00:00"),
    id: 103,
  },
  {
    player1: {
      id: 1,
      name: "Qwe",
    },
    player2: {
      id: 7,
      name: "Def",
    },
    player2goals: 0,
    player1goals: 3,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T11:49:21.709+00:00"),
    id: 99,
  },
  {
    player1: {
      id: 8,
      name: "New Player 5",
    },
    player2: {
      id: 9,
      name: "Cde",
    },
    player2goals: 0,
    player1goals: 2,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T11:48:39.637+00:00"),
    id: 98,
  },
  {
    player1: {
      id: 2,
      name: "Abc",
    },
    player2: {
      id: 4,
      name: "Player4",
    },
    player2goals: 12,
    player1goals: 0,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T11:28:51.671+00:00"),
    id: 97,
  },
  {
    player1: {
      id: 2,
      name: "Abc",
    },
    player2: {
      id: 5,
      name: "Another new player",
    },
    player2goals: 0,
    player1goals: 1,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T11:27:56.221+00:00"),
    id: 96,
  },
];

let expectedLeaderboard: list(playerStats) = [
  {
    playerName: "NewP1",
    matchesWon: 1,
    matchesLost: 0,
    matchesDrawn: 0,
    goalsScored: 2,
    goalsConceded: 1,
  },
  {
    playerName: "New Player 5",
    matchesWon: 1,
    matchesLost: 0,
    matchesDrawn: 0,
    goalsScored: 2,
    goalsConceded: 0,
  },
  {
    playerName: "Abc",
    matchesWon: 4,
    matchesLost: 2,
    matchesDrawn: 1,
    goalsScored: 18,
    goalsConceded: 22,
  },
  {
    playerName: "Yet another one",
    matchesWon: 2,
    matchesLost: 1,
    matchesDrawn: 0,
    goalsScored: 19,
    goalsConceded: 16,
  },
  {
    playerName: "Qwe",
    matchesWon: 2,
    matchesLost: 2,
    matchesDrawn: 1,
    goalsScored: 9,
    goalsConceded: 11,
  },
  {
    playerName: "Another new player",
    matchesWon: 1,
    matchesLost: 1,
    matchesDrawn: 0,
    goalsScored: 4,
    goalsConceded: 2,
  },
  {
    playerName: "Player4",
    matchesWon: 1,
    matchesLost: 2,
    matchesDrawn: 0,
    goalsScored: 24,
    goalsConceded: 18,
  },
  {
    playerName: "Def",
    matchesWon: 0,
    matchesLost: 2,
    matchesDrawn: 0,
    goalsScored: 4,
    goalsConceded: 9,
  },
  {
    playerName: "NewP2",
    matchesWon: 0,
    matchesLost: 1,
    matchesDrawn: 0,
    goalsScored: 1,
    goalsConceded: 2,
  },
  {
    playerName: "Cde",
    matchesWon: 0,
    matchesLost: 1,
    matchesDrawn: 0,
    goalsScored: 0,
    goalsConceded: 2,
  },
];

describe("getLeaderboard", () => {
  test("should return empty leaderboard for empty result list", () => {
    let leaderboard = getLeaderboard([]);
    expect(leaderboard) |> toBe([]);
  });

  test("should return leaderboard with two entries for single result", () => {
    let singleResult = {
      id: 0,
      player1: {
        id: 1,
        name: "Bob",
      },
      player2: {
        id: 2,
        name: "Alice",
      },
      player1goals: 2,
      player2goals: 3,
      extratime: false,
      date: Js.Date.fromString("2019-07-27T07:26:31.667+00:00"),
    };
    let expectedLeaderboard = [
      {
        playerName: "Alice",
        matchesWon: 1,
        matchesLost: 0,
        matchesDrawn: 0,
        goalsScored: 3,
        goalsConceded: 2,
      },
      {
        playerName: "Bob",
        matchesWon: 0,
        matchesLost: 1,
        matchesDrawn: 0,
        goalsScored: 2,
        goalsConceded: 3,
      },
    ];

    let leaderboard = getLeaderboard([singleResult]) |> List.sort(byName);
    expect(leaderboard) |> toEqual(expectedLeaderboard |> List.sort(byName));
  });

  test("should return expected leaderboard for result list", () => {
    let leaderboard = getLeaderboard(testResults) |> List.sort(byName);
    expect(leaderboard) |> toEqual(expectedLeaderboard |> List.sort(byName));
  });
});
