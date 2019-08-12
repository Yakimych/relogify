[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~disabled: bool=?,
    ~checked: bool=?,
    ~color: string=?,
    ~onClick: 'a=?,
    unit
  ) =>
  React.element =
  "Checkbox";
