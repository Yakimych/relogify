[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    {ReasonReact.string("url: ")}
    <ul>
      {url.path
       |> List.map(p => <li> {ReasonReact.string(p)} </li>)
       |> Array.of_list
       |> ReasonReact.array}
    </ul>
  </div>;
};
