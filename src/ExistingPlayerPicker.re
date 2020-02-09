open Utils;
open Queries;
open ApolloHooks;

[@react.component]
let make =
    (
      ~communityName: string,
      ~selectedPlayerId: int,
      ~disabled: bool,
      ~onChange: int => unit,
    ) => {
  let (playersQuery, _) =
    useQuery(
      ~variables=AllPlayersQuery.makeVariables(~communityName, ()),
      AllPlayersQuery.definition,
    );

  switch (playersQuery) {
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    <MaterialUi_NativeSelect
      disabled
      style={ReactDOMRe.Style.make(~width="200px", ())}
      onChange={e => {
        let newId = ReactEvent.Form.target(e)##value;
        onChange(newId);
      }}
      value={string_of_int(selectedPlayerId)}
      input={
        <MaterialUi_OutlinedInput
          style={ReactDOMRe.Style.make(~width="60px", ())}
          labelWidth={`Int(0)}
        />
      }>
      {data##players
       ->Belt.Array.map(p =>
           <option value={string_of_int(p##id)} key={"players_" ++ p##name}>
             {text(p##name)}
           </option>
         )
       ->React.array}
    </MaterialUi_NativeSelect>
  };
};
