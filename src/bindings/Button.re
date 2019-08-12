[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~disabled: bool=?,
    ~variant: string=?,
    ~color: string=?,
    ~onClick: 'a=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "Button";
