[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~variant: string=?,
    ~gutterBottom: bool=?,
    ~component: string=?,
    ~children: React.element,
    unit
  ) =>
  React.element =
  "Typography";
