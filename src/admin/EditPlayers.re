open Utils;
open Types;

// TODO: Expose this as a fragment and lift the query up to the CommunityAdminPage?
module Query = [%relay.query
  {|
    query EditPlayersQuery($communityName: String!) {
      players_connection(where: { community: { name: { _eq: $communityName } } }) {
        edges {
          node {
            id
            name
          }
        }
      }
    }
  |}
];

[@react.component]
let make = (~communityName: string) => {
  let queryData = Query.use(~variables={communityName: communityName}, ());
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
          {queryData.players_connection.edges
           ->Belt.Array.map(p =>
               <MaterialUi.TableRow key={p.node.id}>
                 <MaterialUi.TableCell>
                   {text(p.node.name)}
                 </MaterialUi.TableCell>
               </MaterialUi.TableRow>
             )
           |> React.array}
        </MaterialUi.TableBody>
      </MaterialUi.Table>
    </MaterialUi.Container>
  </>;
};
