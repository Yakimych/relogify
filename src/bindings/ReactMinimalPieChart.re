type dataType = {
  .
  "title": string,
  "value": int,
  "color": string,
};

[@bs.module "react-minimal-pie-chart"] [@react.component]
external make:
  (
    ~style: ReactDOMRe.Style.t=?,
    ~labelStyle: ReactDOMRe.Style.t=?,
    ~animate: bool=?,
    ~label: bool=?,
    ~lineWidth: int=?,
    ~labelWidth: int=?,
    ~data: array(dataType),
    unit
  ) =>
  React.element =
  "default";
