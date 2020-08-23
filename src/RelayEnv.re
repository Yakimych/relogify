[@bs.val]
external apiBaseUrl: string = "process.env.REACT_APP_RELAY_API_BASE_URL";

exception Graphql_error(string);

let fetchQuery: ReasonRelay.Network.fetchFunctionPromise =
  (operation, variables, _cacheConfig) =>
    Fetch.(
      fetchWithInit(
        "https://" ++ apiBaseUrl,
        RequestInit.make(
          ~method_=Post,
          ~body=
            Js.Dict.fromList([
              ("query", Js.Json.string(operation.text)),
              ("variables", variables),
            ])
            |> Js.Json.object_
            |> Js.Json.stringify
            |> BodyInit.make,
          ~headers=
            HeadersInit.make({
              "content-type": "application/json",
              "accept": "application/json",
            }),
          (),
        ),
      )
      |> Js.Promise.then_(resp =>
           if (Response.ok(resp)) {
             Response.json(resp);
           } else {
             Js.Promise.reject(
               Graphql_error(
                 "Request failed: " ++ Response.statusText(resp),
               ),
             );
           }
         )
    );

let subscriptionClient =
  SubscriptionsTransportWs.createSubscriptionClient(
    "wss://" ++ apiBaseUrl,
    {"reconnect": true},
  );

let subscriptionFunction: ReasonRelay.Network.subscribeFn =
  (config, variables, _cacheConfig) => {
    let query = config.text;
    let subscriptionQuery: SubscriptionsTransportWs.requestParams = {
      query,
      variables,
    };

    ReasonRelay.Observable.make(sink => {
      let observable = subscriptionClient##request(subscriptionQuery);
      let subscription = observable##subscribe(sink);
      Some(subscription);
    });
  };

let network =
  ReasonRelay.Network.makePromiseBased(
    ~fetchFunction=fetchQuery,
    ~subscriptionFunction,
    (),
  );

let environment =
  ReasonRelay.Environment.make(
    ~network,
    ~store=
      ReasonRelay.Store.make(
        ~source=ReasonRelay.RecordSource.make(),
        ~gcReleaseBufferSize=50,
        (),
      ),
    (),
  );
