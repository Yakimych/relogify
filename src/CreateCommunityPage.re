open Utils;
open Queries;
open ApolloHooks;

[@react.component]
let make = () => {
  let (communityName, setCommunityName) = React.useState(_ => "");
  let (allCommunitiesResult, _) = useQuery(AllCommunitiesQuery.definition);

  let nameIsAvailable = () =>
    switch (communityName, allCommunitiesResult) {
    | ("new", _) => Some(false)
    | ("", _)
    | (_, Loading)
    | (_, NoData)
    | (_, Error(_)) => None
    | (_, Data(data)) =>
      Some(!data##communities->Belt.Array.some(c => c##name == communityName))
    };

  <>
    <Header page=CreateCommunityPage />
    <Paper>
      <div className="title">
        <Typography variant="h6">
          {React.string("Check availability and create")}
        </Typography>
      </div>
      <div className="panel-content">
        <div className="row">
          <TextField
            style={ReactDOMRe.Style.make(~width="250px", ())}
            value=communityName
            placeholder="Choose a name"
            inputProps={"maxLength": 20}
            onChange={e => {
              let newName = ReactEvent.Form.target(e)##value;
              setCommunityName(_ => newName);
            }}
          />
          <div>
            <div className="availability-indicator">
              <Zoom
                _in={nameIsAvailable()->Belt.Option.getWithDefault(false)}>
                <div> <CheckCircle fontSize="large" htmlColor="green" /> </div>
              </Zoom>
            </div>
            <div className="availability-indicator">
              <Zoom
                _in={!nameIsAvailable()->Belt.Option.getWithDefault(true)}>
                <NotAvailable fontSize="large" htmlColor="red" />
              </Zoom>
            </div>
          </div>
        </div>
      </div>
    </Paper>
    <RouteLink toPage={CommunityStart(communityName)} className="button-link">
      <Button
        variant="contained"
        color="primary"
        disabled={!nameIsAvailable()->Belt.Option.getWithDefault(false)}
        style={ReactDOMRe.Style.make(~marginTop="10px", ())}>
        {text("Take me there!")}
      </Button>
    </RouteLink>
  </>;
};
