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

[@react.component]
let make =
    (
      ~playerPickerFragment,
      ~selectedPlayerId: string,
      ~disabled: bool,
      ~onChange: string => unit,
    ) => {
  let queryData = ExistingPlayerPickerFragment.use(playerPickerFragment);

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
     ->Belt.Array.map(p =>
         <option value={p.node.id} key={"players_" ++ p.node.name}>
           {text(p.node.name)}
         </option>
       )
     ->React.array}
  </MaterialUi.NativeSelect>;
};
