[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~label: string=?,
    ~color: string=?,
    ~variant: string=?,
    unit
  ) =>
  React.element =
  "Chip";
