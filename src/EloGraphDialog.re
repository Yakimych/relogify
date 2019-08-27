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
      <Chip
        style={ReactDOMRe.Style.make(~marginRight="10px", ())}
        label="BETA"
        color="primary"
      />
      {text("Rating graph: " ++ playerName)}
    </DialogTitle>
    <DialogContent> <EloGraph playerName resultsWithRatings /> </DialogContent>
    <DialogActions>
      <Button onClick=onClose color="primary"> {text("Close")} </Button>
    </DialogActions>
  </Dialog>;
