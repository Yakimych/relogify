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
    <MaterialUi_Paper>
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
              <MaterialUi_Zoom
                in_={nameIsAvailable()->Belt.Option.getWithDefault(false)}>
                <div> <CheckCircle fontSize="large" htmlColor="green" /> </div>
              </MaterialUi_Zoom>
            </div>
            <div className="availability-indicator">
              <MaterialUi_Zoom
                in_={!nameIsAvailable()->Belt.Option.getWithDefault(true)}>
                <NotAvailable fontSize="large" htmlColor="red" />
              </MaterialUi_Zoom>
            </div>
          </div>
        </div>
      </div>
    </MaterialUi_Paper>
    <RouteLink toPage={CommunityStart(communityName)} className="button-link">
      <MaterialUi_Button
        variant=`Contained
        color=`Primary
        disabled={!nameIsAvailable()->Belt.Option.getWithDefault(false)}
        style={ReactDOMRe.Style.make(~marginTop="10px", ())}>
        {text("Take me there!")}
      </MaterialUi_Button>
    </RouteLink>
  </>;
};
