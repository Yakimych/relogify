open Utils;

[@react.component]
let make = () => {
  let (communityName, setCommunityName) = React.useState(_ => "");
  let (showAvailabilityIndicator, setShowAvailabilityIndicator) =
    React.useState(_ => false);

  let testAvailability = () => setShowAvailabilityIndicator(_ => true);

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
            onChange={e => {
              setShowAvailabilityIndicator(_ => false);
              let newName = ReactEvent.Form.target(e)##value;
              setCommunityName(_ => newName);
            }}
          />
          {showAvailabilityIndicator
             ? <div>
                 <CommunityAvailabilityIndicator name=communityName />
               </div>
             : React.null}
        </div>
        <Button
          variant="contained"
          color="primary"
          disabled={communityName === ""}
          onClick=testAvailability
          style={ReactDOMRe.Style.make(~marginTop="10px", ())}>
          {text("Check Availability")}
        </Button>
      </div>
    </Paper>
  </>;
};
