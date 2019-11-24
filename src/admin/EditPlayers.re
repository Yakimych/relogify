open Utils;
open Queries;
open Types;

[@react.component]
let make = (~communityName: string) => {
  let playersQueryConfig = AllPlayersQueryConfig.make(~communityName, ());
  let (playersQuery, _) =
    AllPlayersQuery.use(~variables=playersQueryConfig##variables, ());

  switch (playersQuery) {
  | Loading => <CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(data) =>
    <>
      <Header page={AdminPlayersPage(communityName)} />
      <Container maxWidth="sm">
        <Table size="small">
          <TableHead>
            <TableRow>
              <TableCell> {text("Edit")} </TableCell>
              <TableCell> {text("Player")} </TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {data##players
             ->Belt.Array.map(p =>
                 <TableRow key={string_of_int(p##id)}>
                   <TableCell>
                     <button> {text("Edit")} </button>
                     <button> {text("Delete")} </button>
                   </TableCell>
                   <TableCell> {text(p##name)} </TableCell>
                 </TableRow>
               )
             |> React.array}
          </TableBody>
        </Table>
      </Container>
    </>
  };
};
