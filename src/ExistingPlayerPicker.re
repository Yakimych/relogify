open Utils;

module ExistingPlayerPickerFragment = [%relay.fragment
  {|
    fragment ExistingPlayerPicker_Players on playersConnection {
      edges {
        node {
          id
          name
        }
      }
    }
  |}
];

let distinctNodeValues =
    (edges: array(ExistingPlayerPicker_Players_graphql.Types.fragment_edges)) =>
  edges
  ->Belt.Array.map(e => (e.node.id, e.node))
  ->Belt_MapString.fromArray
  ->Belt_MapString.toArray
  ->Belt.Array.map(((_, value)) => value);

[@react.component]
let make =
    (
      ~existingPlayerPickerFragment,
      ~selectedPlayerId: string,
      ~disabled: bool,
      ~onChange: string => unit,
    ) => {
  let queryData =
    ExistingPlayerPickerFragment.use(existingPlayerPickerFragment);

  <MaterialUi.NativeSelect
    disabled
    style={ReactDOMRe.Style.make(~width="200px", ())}
    onChange={e => {
      let newId = ReactEvent.Form.target(e)##value;
      onChange(newId);
    }}
    value=selectedPlayerId
    input={
      <MaterialUi.OutlinedInput
        style={ReactDOMRe.Style.make(~width="60px", ())}
        labelWidth={`Int(0)}
      />
    }>
    {queryData.edges
     ->distinctNodeValues
     ->Belt.Array.map(p =>
         <option value={p.id} key={"players_" ++ p.name}>
           {text(p.name)}
         </option>
       )
     ->React.array}
  </MaterialUi.NativeSelect>;
};
