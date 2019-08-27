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
      {ReasonReact.string("Rating graph: " ++ playerName)}
    </DialogTitle>
    <DialogContent> <EloGraph playerName resultsWithRatings /> </DialogContent>
    <DialogActions>
      <Button onClick=onClose color="primary">
        {ReasonReact.string("Close")}
      </Button>
    </DialogActions>
  </Dialog>;
