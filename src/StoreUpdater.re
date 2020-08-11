let updateResultList =
    (
      store: ReasonRelay.RecordSourceSelectorProxy.t,
      insertedResultId: string,
      connectionKey: string,
    ) =>
  switch (
    store->ReasonRelay.RecordSourceSelectorProxy.get(
      ~dataId=insertedResultId->ReasonRelay.makeDataId,
    )
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
      insertedPlayerId: string,
      connectionKey: string,
    ) => {
  switch (
    store->ReasonRelay.RecordSourceSelectorProxy.get(
      ~dataId=insertedPlayerId->ReasonRelay.makeDataId,
    )
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
