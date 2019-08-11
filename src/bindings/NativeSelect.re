[@bs.module "@material-ui/core"] [@react.component]
external make:
  (
    ~disabled: bool=?,
    ~className: string=?,
    ~style: ReactDOMRe.Style.t=?,
    ~value: string=?,
    ~onChange: 'a=?,
    ~input: React.element=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "NativeSelect";
