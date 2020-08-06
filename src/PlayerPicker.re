open Utils;

let newPlayerValue = "NEW_PLAYER";

module PlayerPickerFragment = [%relay.fragment
  {|
    fragment PlayerPicker_Players on playersConnection {
      edges {
        node {
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
      ~selectedPlayerName: option(string),
      ~disabled: bool,
      ~placeholderText: option(string)=?,
      ~onChange: string => unit,
      ~allowNewPlayer: bool=true,
    ) => {
  let queryData = PlayerPickerFragment.use(playerPickerFragment);

  let (isInCustomMode, setIsInCustomMode) = React.useState(_ => false);

  let handleSelectChange = (value: string) =>
    if (value === newPlayerValue) {
      onChange("");
      setIsInCustomMode(_ => true);
    } else {
      onChange(value);
    };

  React.useEffect1(
    _ => {
      if (selectedPlayerName->Belt.Option.isNone) {
        setIsInCustomMode(_ => false);
      };
      None;
    },
    [|selectedPlayerName|],
  );

  let playerNames = queryData.edges->Belt.Array.map(p => p.node.name);

  isInCustomMode || Belt.Array.length(playerNames) === 0
    ? <MaterialUi.TextField
        disabled
        className="highlighted"
        autoFocus=true
        style={ReactDOMRe.Style.make(~width="200px", ())}
        variant=`Outlined
        inputProps={"maxLength": 20}
        value={`String(selectedPlayerName->Belt.Option.getWithDefault(""))}
        onChange={e => {
          let newName = ReactEvent.Form.target(e)##value;
          onChange(newName);
        }}
      />
    : <MaterialUi.NativeSelect
        disabled
        style={ReactDOMRe.Style.make(~width="200px", ())}
        onChange={e => {
          let newName = ReactEvent.Form.target(e)##value;
          handleSelectChange(newName);
        }}
        value={selectedPlayerName->Belt.Option.getWithDefault("")}
        input={
          <MaterialUi.OutlinedInput
            style={ReactDOMRe.Style.make(~width="60px", ())}
            labelWidth={`Int(0)}
          />
        }>
        <option key="empty" value="" disabled=true>
          {text(placeholderText->Belt.Option.getWithDefault(""))}
        </option>
        {playerNames
         ->Belt.Array.map(p =>
             <option value=p key={"players_" ++ p}> {text(p)} </option>
           )
         ->React.array}
        {allowNewPlayer
           ? <option key="new_player" value=newPlayerValue>
               {text("+ Add new player")}
             </option>
           : React.null}
      </MaterialUi.NativeSelect>;
};
