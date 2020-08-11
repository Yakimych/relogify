let updateResultList =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      insertedResultId: ReasonRelay.dataId,
      connectionKey: string,
    ) =>
  switch (
    store->ReasonRelay.RecordSourceSelectorProxy.get(~dataId=insertedResultId)
  ) {
  | Some(node) =>
    ReasonRelayUtils.createAndAddEdgeToConnections(
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
  };

let updatePlayerList =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      insertedPlayerId: ReasonRelay.dataId,
      connectionKey: string,
    ) => {
  switch (
    store->ReasonRelay.RecordSourceSelectorProxy.get(~dataId=insertedPlayerId)
  ) {
  | Some(playerResult) =>
    ReasonRelayUtils.createAndAddEdgeToConnections(
      ~store,
      ~node=playerResult,
      ~connections=[
        {
          parentID: ReasonRelay.storeRootId,
          key: connectionKey,
          filters: None,
        },
      ],
      ~edgeName="playersEdge",
      ~insertAt=End,
    )
  | None => ()
  };
};
