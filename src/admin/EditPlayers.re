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
        <Table size="small">
          <TableHead>
            <TableRow> <TableCell> {text("Player")} </TableCell> </TableRow>
          </TableHead>
          <TableBody>
            {data##players
             ->Belt.Array.map(p =>
                 <TableRow key={string_of_int(p##id)}>
                   <TableCell> {text(p##name)} </TableCell>
                 </TableRow>
               )
             |> React.array}
          </TableBody>
        </Table>
      </MaterialUi_Container>
    </>
  };
};
