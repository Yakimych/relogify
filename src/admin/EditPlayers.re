open Utils;
open Types;

module EditPlayersFragment = [%relay.fragment
  {|
    fragment EditPlayersFragment_Players on playersConnection {
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
let make = (~communityName: string, ~editPlayersFragment) => {
  let players = EditPlayersFragment.use(editPlayersFragment);
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
          {players.edges
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
