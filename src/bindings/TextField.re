[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~disabled: bool=?,
    ~className: string=?,
    ~autoFocus: bool=?,
    ~type_: string=?,
    ~style: ReactDOMRe.Style.t=?,
    ~variant: string=?,
    ~value: string=?,
    ~onChange: 'a=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "TextField";
