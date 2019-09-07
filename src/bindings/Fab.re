[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~size: string=?,
    ~color: string=?,
    ~className: string=?,
    ~children: React.element,
    unit
  ) =>
  React.element =
  "Fab";
