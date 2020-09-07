open Utils;

module Query = [%relay.query
  {|
    query CreateCommunityPageQuery {
      communities_connection {
        edges {
          node {
            name
          }
        }
      }
    }
  |}
];

[@react.component]
let make = () => {
  let (communityName, setCommunityName) = React.useState(_ => "");
  let queryData = Query.use(~variables=(), ());

  let nameIsAvailable = () =>
    switch (communityName) {
    | "" => None
    | "new" => Some(false)
    | _ =>
      Some(
        queryData.communities_connection.edges
        |> Array.exists(
             (
               communityEdge: Query.Types.response_communities_connection_edges,
             ) =>
             communityEdge.node.name == communityName
           )
        |> (!),
      )
    };

  <>
    <Header page=CreateCommunityPage />
    <MaterialUi.Paper>
      <div className="title">
        <MaterialUi.Typography variant=`H6>
          {text("Check availability and create")}
        </MaterialUi.Typography>
      </div>
      <div className="panel-content">
        <div className="row">
          <MaterialUi.TextField
            style={ReactDOMRe.Style.make(~width="250px", ())}
            value={`String(communityName)}
            placeholder="Choose a name"
            inputProps={"maxLength": 20}
            onChange={e => {
              let newName = ReactEvent.Form.target(e)##value;
              setCommunityName(_ => newName);
            }}
          />
          <div>
            <div className="availability-indicator">
              <MaterialUi.Zoom
                in_={nameIsAvailable()->Belt.Option.getWithDefault(false)}>
                <div> <CheckCircle fontSize="large" htmlColor="green" /> </div>
              </MaterialUi.Zoom>
            </div>
            <div className="availability-indicator">
              <MaterialUi.Zoom
                in_={!nameIsAvailable()->Belt.Option.getWithDefault(true)}>
                <NotAvailable fontSize="large" htmlColor="red" />
              </MaterialUi.Zoom>
            </div>
          </div>
        </div>
      </div>
    </MaterialUi.Paper>
    <RouteLink toPage={CommunityStart(communityName)} className="button-link">
      <MaterialUi.Button
        variant=`Contained
        color=`Primary
        disabled={!nameIsAvailable()->Belt.Option.getWithDefault(false)}
        style={ReactDOMRe.Style.make(~marginTop="10px", ())}>
        {text("Take me there!")}
      </MaterialUi.Button>
    </RouteLink>
  </>;
};
