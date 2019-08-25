/*
 See https://metinmediamath.wordpress.com/2013/11/27/how-to-calculate-the-elo-rating-including-example/
 for details about the used formula. K-factor of 32 has been chosen for the current implementation.
 */
open Types;

type resultType =
  | Win
  | Loss
  | Draw;

let initialRating = 1200.0;
let initialRatings: Belt_MapString.t(float) = Belt_MapString.empty;

let kFactor = 32.0;

let getR = (rating: float) =>
  Js.Math.pow_float(~base=10.0, ~exp=rating /. 400.0);

let getE1 = (r1: float, r2: float) => r1 /. (r1 +. r2);
let getE2 = (r1: float, r2: float) => r2 /. (r1 +. r2);

let getResultType = (result: result, playerName: string): resultType =>
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
    (ratings: Belt_MapString.t(float), result: result)
    : Belt_MapString.t(float) => {
  let player1Rating =
    ratings->Belt_MapString.getWithDefault(
      result.player1.name,
      initialRating,
    );
  let player2Rating =
    ratings->Belt_MapString.getWithDefault(
      result.player2.name,
      initialRating,
    );

  let resultTypePlayer1 = getResultType(result, result.player1.name);
  let resultTypePlayer2 = getResultType(result, result.player2.name);

  ratings
  ->Belt_MapString.set(
      result.player1.name,
      getNewRating(player1Rating, player2Rating, resultTypePlayer1),
    )
  ->Belt_MapString.set(
      result.player2.name,
      getNewRating(player2Rating, player1Rating, resultTypePlayer2),
    );
};

let getEloRankings = (results: list(result)): Belt_MapString.t(float) =>
  results->Belt.List.reduce(Belt_MapString.empty, eloRatingReducer);
