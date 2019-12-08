let canAddResult =
    (
      allowDraws,
      maybePlayer1Name,
      maybePlayer2Name,
      goals1,
      goals2,
      extraTime,
    ) =>
  switch (maybePlayer1Name, maybePlayer2Name, goals1, goals2, extraTime) {
  | (None | Some(""), _, _, _, _)
  | (_, None | Some(""), _, _, _) =>
    Belt.Result.Error("You must select both players!")
  | (_, _, goals1, goals2, _) when goals1 === goals2 && !allowDraws =>
    Belt.Result.Error("A game cannot end in a draw!")
  | (_, _, goals1, goals2, extraTime)
      when Js.Math.abs_int(goals1 - goals2) != 1 && extraTime =>
    Belt.Result.Error(
      "Games with Extra Time cannot have more than one goal difference!",
    )
  | (Some(player1Name), Some(player2Name), _, _, _)
      when player1Name === player2Name =>
    Belt.Result.Error("You must select two DIFFERENT players!")
  | (Some(player1Name), Some(player2Name), _, _, _) =>
    Belt.Result.Ok((player1Name, player2Name))
  };
