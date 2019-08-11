[@react.component]
let make =
    (~url: string, ~style: ReactDOMRe.Style.t=?, ~children: React.element) =>
  <a
    href="#"
    style
    onClick={e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReactRouter.push(url);
    }}>
    children
  </a>;
