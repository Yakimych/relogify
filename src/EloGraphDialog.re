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
  <MaterialUi_Dialog onClose={(_, _) => onClose()} open_=isOpen>
    <MaterialUi_DialogTitle>
      <MaterialUi_Chip
        style={ReactDOMRe.Style.make(~marginRight="10px", ())}
        label={React.string("BETA")}
        color=`Primary
      />
      {text("Rating graph: " ++ playerName)}
    </MaterialUi_DialogTitle>
    <MaterialUi_DialogContent>
      <EloGraph playerName resultsWithRatings />
    </MaterialUi_DialogContent>
    <MaterialUi_DialogActions>
      <MaterialUi_Button onClick={_ => onClose()} color=`Primary>
        {text("Close")}
      </MaterialUi_Button>
    </MaterialUi_DialogActions>
  </MaterialUi_Dialog>;
