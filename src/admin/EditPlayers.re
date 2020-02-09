open Utils;
open Queries;
open Types;
open ApolloHooks;

[@react.component]
let make = (~communityName: string) => {
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
    <>
      <Header page={AdminPlayersPage(communityName)} />
      <MaterialUi_Container maxWidth=`Sm>
        <MaterialUi_Table size=`Small>
          <MaterialUi_TableHead>
            <MaterialUi_TableRow>
              <MaterialUi_TableCell> {text("Player")} </MaterialUi_TableCell>
            </MaterialUi_TableRow>
          </MaterialUi_TableHead>
          <MaterialUi_TableBody>
            {data##players
             ->Belt.Array.map(p =>
                 <MaterialUi_TableRow key={string_of_int(p##id)}>
                   <MaterialUi_TableCell>
                     {text(p##name)}
                   </MaterialUi_TableCell>
                 </MaterialUi_TableRow>
               )
             |> React.array}
          </MaterialUi_TableBody>
        </MaterialUi_Table>
      </MaterialUi_Container>
    </>
  };
};
