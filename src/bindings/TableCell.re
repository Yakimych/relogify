[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~align: string=?,
    ~title: string=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "TableCell";
