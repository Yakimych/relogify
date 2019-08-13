[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~active: bool=?,
    ~direction: string=?,
    ~onClick: 'a=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "TableSortLabel";
