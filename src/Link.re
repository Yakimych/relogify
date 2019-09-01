[@react.component]
let make =
    (
      ~url: string,
      ~className: string=?,
      ~style: ReactDOMRe.Style.t=?,
      ~children: React.element,
    ) =>
  <a
    href="#"
    className
    style
    onClick={e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReactRouter.push(url);
    }}>
    children
  </a>;
