[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~badgeContent: string=?,
    ~color: string=?,
    ~children: React.element,
    unit
  ) =>
  React.element =
  "Badge";
