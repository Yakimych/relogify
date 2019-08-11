[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~size: string,
    ~children: React.element,
    unit
  ) =>
  React.element =
  "Table";
