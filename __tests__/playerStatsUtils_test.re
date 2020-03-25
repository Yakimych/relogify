open Jest;
open Expect;
open Types;
open PlayerStatsUtils;

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
      id: 5,
      name: "Another new player",
    },
    player2: {
      id: 6,
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
      id: 9,
      name: "Player4",
    },
    player2: {
      id: 6,
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
      id: 10,
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
      id: 11,
      name: "New Player 5",
    },
    player2: {
      id: 12,
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
      id: 9,
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
      id: 6,
      name: "Another new player",
    },
    player2goals: 0,
    player1goals: 1,
    extratime: false,
    date: Js.Date.fromString("2019-07-21T11:27:56.221+00:00"),
    id: 96,
  },
];

let expectedPlayerStatsForAbc: playerStats = {
  playerName: "Abc",
  matchesWon: 4,
  matchesLost: 2,
  matchesDrawn: 0,
  goalsScored: 15,
  goalsConceded: 19,
};

let emptyPlayerStats = (playerName: string) => {
  playerName,
  goalsScored: 0,
  goalsConceded: 0,
  matchesWon: 0,
  matchesLost: 0,
  matchesDrawn: 0,
};

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

describe("getLeaderboard", () => {
  test("should return empty leaderboard for empty result list", () =>
    expect(getPlayerStats("", [])) |> toEqual(emptyPlayerStats(""))
  );

  test("should return expected stats for first player", () => {
    let expectedPlayerStats = {
      playerName: "Alice",
      matchesWon: 1,
      matchesLost: 0,
      matchesDrawn: 0,
      goalsScored: 3,
      goalsConceded: 2,
    };

    let playerStats = getPlayerStats("Alice", [singleResult]);
    expect(playerStats) |> toEqual(expectedPlayerStats);
  });

  test("should return expected stats for second player", () => {
    let expectedPlayerStats = {
      playerName: "Bob",
      matchesWon: 0,
      matchesLost: 1,
      matchesDrawn: 0,
      goalsScored: 2,
      goalsConceded: 3,
    };

    let playerStats = getPlayerStats("Bob", [singleResult]);
    expect(playerStats) |> toEqual(expectedPlayerStats);
  });

  test("should return expected leaderboard for result list", () => {
    let playerStats = getPlayerStats("Abc", testResults);
    expect(playerStats) |> toEqual(expectedPlayerStatsForAbc);
  });
});

let testPlayer1: player = {id: 1, name: "Player1"};
let testPlayer2: player = {id: 2, name: "Player2"};

let testMatchResult: matchResult = {
  id: 1,
  player1: testPlayer1,
  player2: testPlayer2,
  player1goals: 0,
  player2goals: 0,
  date: Js.Date.fromString("2019-01-01"),
  extratime: false,
};

describe("hasPlayer1Won", () => {
  test("should return true when player1 has more points than player2", () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 2,
      player2goals: 1,
    };
    expect(hasPlayer1Won(result)) |> toBe(true);
  });

  test(
    "should return false when player1 has the same number of points as player2",
    () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 2,
      player2goals: 2,
    };
    expect(hasPlayer1Won(result)) |> toBe(false);
  });

  test("should return false when player1 has fewer points than player2", () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 1,
      player2goals: 2,
    };
    expect(hasPlayer1Won(result)) |> toBe(false);
  });
});

describe("hasPlayer2Won", () => {
  test("should return true when player2 has more points than player1", () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 0,
      player2goals: 5,
    };
    expect(hasPlayer2Won(result)) |> toBe(true);
  });

  test(
    "should return false when player2 has the same number of points as player1",
    () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 0,
      player2goals: 0,
    };
    expect(hasPlayer2Won(result)) |> toBe(false);
  });

  test("should return false when player2 has fewer points than player1", () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 3,
      player2goals: 1,
    };
    expect(hasPlayer2Won(result)) |> toBe(false);
  });
});

describe("hasMainPlayerWon", () => {
  test(
    "should return true when player1 is main player and has more points than player2",
    () => {
      let result: matchResult = {
        ...testMatchResult,
        player1goals: 1,
        player2goals: 0,
      };
      expect(hasMainPlayerWon(Some(testPlayer1.name), result))
      |> toBe(true);
    },
  );

  test(
    "should return false when player1 has the same number of points as player2",
    () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 5,
      player2goals: 5,
    };
    expect(hasMainPlayerWon(Some(testPlayer1.name), result)) |> toBe(false);
  });

  test(
    "should return false when player1 is the main player and has fewer points than player2",
    () => {
      let result: matchResult = {
        ...testMatchResult,
        player1goals: 1,
        player2goals: 4,
      };
      expect(hasMainPlayerWon(Some(testPlayer1.name), result))
      |> toBe(false);
    },
  );

  test(
    "should return true when player2 is main player and has more points than player1",
    () => {
      let result: matchResult = {
        ...testMatchResult,
        player1goals: 1,
        player2goals: 2,
      };
      expect(hasMainPlayerWon(Some(testPlayer2.name), result))
      |> toBe(true);
    },
  );

  test(
    "should return false when player2 has the same number of points as player1",
    () => {
    let result: matchResult = {
      ...testMatchResult,
      player1goals: 3,
      player2goals: 3,
    };
    expect(hasMainPlayerWon(Some(testPlayer2.name), result)) |> toBe(false);
  });

  test(
    "should return false when player2 is the main player and has fewer points than player1",
    () => {
      let result: matchResult = {
        ...testMatchResult,
        player1goals: 2,
        player2goals: 0,
      };
      expect(hasMainPlayerWon(Some(testPlayer2.name), result))
      |> toBe(false);
    },
  );
});
