[@bs.module "@material-ui/core"] [@react.component]
external make:
  (~children: React.element, ~expanded: bool=?, unit) => React.element =
  "ExpansionPanel";
