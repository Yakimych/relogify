/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri=apiBaseUrl, ());

let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());

let app =
  <ReasonApolloHooks.ApolloProvider client>
    <Routing />
  </ReasonApolloHooks.ApolloProvider>;

ReactDOMRe.renderToElementWithId(app, "root");
