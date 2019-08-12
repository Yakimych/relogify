[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~disabled: bool=?,
    ~className: string=?,
    ~autoFocus: bool=?,
    ~_type: string=?,
    ~style: ReactDOMRe.Style.t=?,
    ~variant: string=?,
    ~value: string=?,
    ~onChange: 'a=?,
    ~inputProps: Js.t({..})=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "TextField";
