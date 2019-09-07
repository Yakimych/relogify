[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~position: string=?,
    ~color: string=?,
    ~className: string=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "AppBar";
