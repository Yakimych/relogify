/*
 See https://metinmediamath.wordpress.com/2013/11/27/how-to-calculate-the-elo-rating-including-example/
 for details about the used formula. K-factor of 32 has been chosen for the current implementation.
 */
open Types;
open Utils;

type eloMap = Belt_MapString.t(float);

type resultWithRatings = {
  result: matchResult,
  player1RatingBefore: float,
  player1RatingAfter: float,
  player2RatingBefore: float,
  player2RatingAfter: float,
};

let resultsWithRatingsByDate =
    (first: resultWithRatings, second: resultWithRatings) =>
  DateFns.compareAsc(first.result.date, second.result.date);

// This is only necessary temporarily while ratings are recalculated on the frontend
type temp_resultsWithRatingMap = {
  ratingMap: eloMap,
  // Ratings are going to be part of the result type as soon as this information is persisted
  resultsWithRatings: list(resultWithRatings),
};

type resultType =
  | Win
  | Loss
  | Draw;

let initialRating = 1200.0;
let initialRatings: eloMap = Belt_MapString.empty;

let kFactor = 32.0;

let getR = (rating: float) =>
  Js.Math.pow_float(~base=10.0, ~exp=rating /. 400.0);

let getE1 = (r1: float, r2: float) => r1 /. (r1 +. r2);
let getE2 = (r1: float, r2: float) => r2 /. (r1 +. r2);

let getResultType = (result: matchResult, playerName: string): resultType =>
  if (result.player1goals === result.player2goals) {
    Draw;
  } else {
    result.player1.name === playerName
    && result.player1goals > result.player2goals
    || result.player2.name === playerName
    && result.player2goals > result.player1goals
      ? Win : Loss;
  };

let getS =
  fun
  | Win => 1.0
  | Draw => 0.5
  | Loss => 0.0;

let getNewRating =
    (playerRating: float, opponentRating: float, resultType: resultType)
    : float => {
  let r1 = getR(playerRating);
  let r2 = getR(opponentRating);
  let e1 = getE1(r1, r2);
  let s = getS(resultType);
  playerRating +. kFactor *. (s -. e1);
};

let eloRatingReducer =
    (state: temp_resultsWithRatingMap, result: matchResult)
    : temp_resultsWithRatingMap => {
  let player1Rating =
    state.ratingMap
    ->Belt_MapString.getWithDefault(result.player1.name, initialRating);
  let player2Rating =
    state.ratingMap
    ->Belt_MapString.getWithDefault(result.player2.name, initialRating);

  let resultTypePlayer1 = getResultType(result, result.player1.name);
  let resultTypePlayer2 = getResultType(result, result.player2.name);

  let newPlayer1Rating =
    getNewRating(player1Rating, player2Rating, resultTypePlayer1);
  let newPlayer2Rating =
    getNewRating(player2Rating, player1Rating, resultTypePlayer2);

  let newRatingMap =
    state.ratingMap
    ->Belt_MapString.set(result.player1.name, newPlayer1Rating)
    ->Belt_MapString.set(result.player2.name, newPlayer2Rating);
  {
    ratingMap: newRatingMap,
    resultsWithRatings: [
      {
        result,
        player1RatingBefore: player1Rating,
        player1RatingAfter: newPlayer1Rating,
        player2RatingBefore: player2Rating,
        player2RatingAfter: newPlayer2Rating,
      },
      ...state.resultsWithRatings,
    ],
  };
};

let attachRatings = (results: list(matchResult)): temp_resultsWithRatingMap =>
  results
  ->Belt.List.sort(resultsByDate)
  ->Belt.List.reduce(
      {ratingMap: Belt_MapString.empty, resultsWithRatings: []},
      eloRatingReducer,
    );

let getOldestRatingForPlayer =
    (playerName, resultsWithRatings: list(resultWithRatings)) => {
  resultsWithRatings
  ->Belt.List.keep(r =>
      r.result.player1.name == playerName
      || r.result.player2.name == playerName
    )
  ->Belt.List.sort(resultsWithRatingsByDate)
  ->Belt.List.head
  ->Belt.Option.map(r =>
      if (r.result.player1.name == playerName) {
        r.player1RatingBefore;
      } else {
        r.player2RatingBefore;
      }
    );
};

let getRatingDiffs =
    (ratingMap: eloMap, resultsWithRatings: list(resultWithRatings)): eloMap => {
  let ratingDiffReducer = (ratingDiffMap, playerName, currentRating) =>
    getOldestRatingForPlayer(playerName, resultsWithRatings)
    ->Belt.Option.mapWithDefault(ratingDiffMap, oldestRating =>
        ratingDiffMap->Belt_MapString.set(
          playerName,
          currentRating -. oldestRating,
        )
      );

  ratingMap->Belt_MapString.reduce(Belt_MapString.empty, ratingDiffReducer);
};
