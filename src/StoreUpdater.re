let updateResultList =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      fieldName: string,
      connectionKey: string,
    ) => {
  ReasonRelayUtils.(
    switch (
      resolveNestedRecord(
        ~rootRecord=
          store->ReasonRelay.RecordSourceSelectorProxy.getRootField(
            ~fieldName,
          ),
        ~path=[],
      )
    ) {
    | Some(node) =>
      createAndAddEdgeToConnections(
        ~store,
        ~node,
        ~connections=[
          {
            parentID: ReasonRelay.storeRootId,
            key: connectionKey,
            filters: None,
          },
        ],
        ~edgeName="resultsEdge",
        ~insertAt=End,
      )
    | None => ()
    }
  );
};

let tryGetPlayerFromMutationResult =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      fieldName: string,
      playerPath: list(string),
    ) =>
  ReasonRelayUtils.resolveNestedRecord(
    ~rootRecord=
      store->ReasonRelay.RecordSourceSelectorProxy.getRootField(~fieldName),
    ~path=playerPath,
  );

let addPlayerToStore =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      connectionKey: string,
      node,
    ) =>
  ReasonRelayUtils.createAndAddEdgeToConnections(
    ~store,
    ~node,
    ~connections=[
      {parentID: ReasonRelay.storeRootId, key: connectionKey, filters: None},
    ],
    ~edgeName="playersEdge",
    ~insertAt=End,
  );

let updatePlayerList =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      fieldName: string,
      connectionKey: string,
      playerPath: list(string),
    ) => {
  switch (tryGetPlayerFromMutationResult(store, fieldName, playerPath)) {
  | Some(playerResult) =>
    addPlayerToStore(store, connectionKey, playerResult)
  | None => ()
  };
};
