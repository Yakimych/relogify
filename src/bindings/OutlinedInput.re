[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~labelWidth: int=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "OutlinedInput";
