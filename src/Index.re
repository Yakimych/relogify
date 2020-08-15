[@bs.val] external identityUrl: string = "process.env.REACT_APP_IDENTITY_URL";

ReactExperimental.renderConcurrentRootAtElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnv.environment>
    <ReactNetlifyIdentity.IdentityContextProvider url=identityUrl>
      <React.Suspense fallback={<div> {React.string("Loading...")} </div>}>
        <Routing />
      </React.Suspense>
    </ReactNetlifyIdentity.IdentityContextProvider>
  </ReasonRelay.Context.Provider>,
  "root",
);
