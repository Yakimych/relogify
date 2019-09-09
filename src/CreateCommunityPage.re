open Utils;

[@react.component]
let make = () => {
  let (communityName, setCommunityName) = React.useState(_ => "");
  let (maybeIsAvailable, setMaybeIsAvailable) = React.useState(_ => None);

  let testAvailability = () => {
    // TODO: Implement API call
    let isAvailable = communityName !== "test";
    setMaybeIsAvailable(_ => Some(isAvailable));
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
            onChange={e => {
              setMaybeIsAvailable(_ => None);
              let newName = ReactEvent.Form.target(e)##value;
              setCommunityName(_ => newName);
            }}
          />
          <div>
            <div className="availability-indicator">
              <Zoom
                _in={
                  maybeIsAvailable->Belt.Option.mapWithDefault(false, a => a)
                }>
                <CheckCircle fontSize="large" htmlColor="green" />
              </Zoom>
            </div>
            <div className="availability-indicator">
              <Zoom
                _in={
                  maybeIsAvailable->Belt.Option.mapWithDefault(false, a => !a)
                }>
                <NotAvailable fontSize="large" htmlColor="red" />
              </Zoom>
            </div>
          </div>
        </div>
        <Button
          variant="contained"
          color="primary"
          onClick=testAvailability
          style={ReactDOMRe.Style.make(~marginTop="10px", ())}>
          {text("Check Availability")}
        </Button>
      </div>
    </Paper>
  </>;
};
