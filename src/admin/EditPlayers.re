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
  | Loading => <MaterialUi.CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    <>
      <Header page={AdminPlayersPage(communityName)} />
      <MaterialUi.Container maxWidth=`Sm>
        <MaterialUi.Table size=`Small>
          <MaterialUi.TableHead>
            <MaterialUi.TableRow>
              <MaterialUi.TableCell> {text("Player")} </MaterialUi.TableCell>
            </MaterialUi.TableRow>
          </MaterialUi.TableHead>
          <MaterialUi.TableBody>
            {data##players
             ->Belt.Array.map(p =>
                 <MaterialUi.TableRow key={string_of_int(p##id)}>
                   <MaterialUi.TableCell>
                     {text(p##name)}
                   </MaterialUi.TableCell>
                 </MaterialUi.TableRow>
               )
             |> React.array}
          </MaterialUi.TableBody>
        </MaterialUi.Table>
      </MaterialUi.Container>
    </>
  };
};
