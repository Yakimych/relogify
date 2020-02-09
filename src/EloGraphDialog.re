open Utils;
open EloUtils;

[@react.component]
let make =
    (
      ~isOpen: bool,
      ~onClose,
      ~playerName: string,
      ~resultsWithRatings: list(resultWithRatings),
    ) =>
  <Dialog onClose _open=isOpen>
    <DialogTitle id="customized-dialog-title" onClose>
      <MaterialUi_Chip
        style={ReactDOMRe.Style.make(~marginRight="10px", ())}
        label={React.string("BETA")}
        color=`Primary
      />
      {text("Rating graph: " ++ playerName)}
    </DialogTitle>
    <DialogContent> <EloGraph playerName resultsWithRatings /> </DialogContent>
    <DialogActions>
      <MaterialUi_Button onClick={_ => onClose()} color=`Primary>
        {text("Close")}
      </MaterialUi_Button>
    </DialogActions>
  </Dialog>;
