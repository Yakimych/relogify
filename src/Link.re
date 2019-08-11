[@react.component]
let make = (~url: string, ~children: React.element) =>
  <a
    href="#"
    onClick={e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReactRouter.push(url);
    }}>
    children
  </a>;
