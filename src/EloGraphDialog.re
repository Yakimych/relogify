open Utils;
open EloUtils;

[@react.component]
let make =
    (
      ~isOpen: bool,
      ~onClose: unit => unit,
      ~playerName: string,
      ~resultsWithRatings: list(resultWithRatings),
    ) =>
  <MaterialUi.Dialog onClose={(_, _) => onClose()} open_=isOpen>
    <MaterialUi.DialogTitle>
      <MaterialUi.Chip
        style={ReactDOMRe.Style.make(~marginRight="10px", ())}
        label={text("BETA")}
        color=`Primary
      />
      {text("Rating graph: " ++ playerName)}
    </MaterialUi.DialogTitle>
    <MaterialUi.DialogContent>
      <EloGraph playerName resultsWithRatings />
    </MaterialUi.DialogContent>
    <MaterialUi.DialogActions>
      <MaterialUi.Button onClick={_ => onClose()} color=`Primary>
        {text("Close")}
      </MaterialUi.Button>
    </MaterialUi.DialogActions>
  </MaterialUi.Dialog>;
