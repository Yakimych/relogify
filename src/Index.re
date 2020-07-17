[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";
[@bs.val] external identityUrl: string = "process.env.REACT_APP_IDENTITY_URL";

/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri="https://" ++ apiBaseUrl, ());

/* WebSocket client */
let webSocketLink =
  ApolloLinks.webSocketLink({
    uri: "wss://" ++ apiBaseUrl,
    options: {
      reconnect: true,
      connectionParams: None,
    },
  });

/* based on test, execute left or right */
let webSocketHttpLink =
  ApolloLinks.split(
    operation => {
      let operationDefition =
        ApolloUtilities.getMainDefinition(operation.query);
      operationDefition.kind == "OperationDefinition"
      && operationDefition.operation == "subscription";
    },
    webSocketLink,
    httpLink,
  );

let client =
  ReasonApollo.createApolloClient(
    ~link=webSocketHttpLink,
    ~cache=inMemoryCache,
    (),
  );

let app =
  <ApolloHooks.Provider client>
    <ReactNetlifyIdentity.IdentityContextProvider url=identityUrl>
      <Routing />
    </ReactNetlifyIdentity.IdentityContextProvider>
  </ApolloHooks.Provider>;

ReactDOMRe.renderToElementWithId(app, "root");
