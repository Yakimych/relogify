[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~elevation: int=?,
    ~children: React.element,
    unit
  ) =>
  React.element =
  "Paper";
