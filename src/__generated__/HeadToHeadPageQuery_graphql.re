/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type response_results_connection = {
    edges: array(response_results_connection_edges),
  }
  and response_results_connection_edges = {
    node: response_results_connection_edges_node,
  }
  and response_results_connection_edges_node = {
    id: string,
    player1: response_results_connection_edges_node_player1,
    player1goals: int,
    player2: response_results_connection_edges_node_player2,
    player2goals: int,
    date: string,
    extratime: bool,
  }
  and response_results_connection_edges_node_player1 = {
    id: string,
    name: string,
  }
  and response_results_connection_edges_node_player2 = {
    id: string,
    name: string,
  };

  type response = {results_connection: response_results_connection};
  type rawResponse = response;
  type refetchVariables = {
    communityName: option(string),
    player1Name: option(string),
    player2Name: option(string),
  };
  let makeRefetchVariables =
      (~communityName=?, ~player1Name=?, ~player2Name=?, ()): refetchVariables => {
    communityName,
    player1Name,
    player2Name,
  };
  type variables = {
    communityName: string,
    player1Name: string,
    player2Name: string,
  };
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {} |json}
  ];
  let responseConverterMap = ();
  let convertResponse = v =>
    v
    ->ReasonRelay._convertObj(
        responseConverter,
        responseConverterMap,
        Js.undefined,
      );

  type rawResponseRaw = responseRaw;
  let convertRawResponse = convertResponse;

  let variablesConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {} |json}
  ];
  let variablesConverterMap = ();
  let convertVariables = v =>
    v
    ->ReasonRelay._convertObj(
        variablesConverter,
        variablesConverterMap,
        Js.undefined,
      );
};

type queryRef;

module Utils = {
  open Types;
  let makeVariables = (~communityName, ~player1Name, ~player2Name): variables => {
    communityName,
    player1Name,
    player2Name,
  };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "communityName"
  },
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "player1Name"
  },
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "player2Name"
  }
],
v1 = [
  {
    "fields": [
      {
        "kind": "Variable",
        "name": "_eq",
        "variableName": "player1Name"
      }
    ],
    "kind": "ObjectValue",
    "name": "name"
  }
],
v2 = [
  {
    "fields": [
      {
        "kind": "Variable",
        "name": "_eq",
        "variableName": "player2Name"
      }
    ],
    "kind": "ObjectValue",
    "name": "name"
  }
],
v3 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v4 = [
  (v3/*: any*/),
  {
    "alias": null,
    "args": null,
    "kind": "ScalarField",
    "name": "name",
    "storageKey": null
  }
],
v5 = [
  {
    "alias": null,
    "args": [
      {
        "kind": "Literal",
        "name": "order_by",
        "value": {
          "date": "desc"
        }
      },
      {
        "fields": [
          {
            "items": [
              {
                "fields": [
                  {
                    "fields": [
                      {
                        "fields": [
                          {
                            "kind": "Variable",
                            "name": "_eq",
                            "variableName": "communityName"
                          }
                        ],
                        "kind": "ObjectValue",
                        "name": "name"
                      }
                    ],
                    "kind": "ObjectValue",
                    "name": "community"
                  }
                ],
                "kind": "ObjectValue",
                "name": "_and.0"
              },
              {
                "fields": [
                  {
                    "items": [
                      {
                        "fields": [
                          {
                            "fields": (v1/*: any*/),
                            "kind": "ObjectValue",
                            "name": "player1"
                          }
                        ],
                        "kind": "ObjectValue",
                        "name": "_or.0"
                      },
                      {
                        "fields": [
                          {
                            "fields": (v1/*: any*/),
                            "kind": "ObjectValue",
                            "name": "player2"
                          }
                        ],
                        "kind": "ObjectValue",
                        "name": "_or.1"
                      }
                    ],
                    "kind": "ListValue",
                    "name": "_or"
                  }
                ],
                "kind": "ObjectValue",
                "name": "_and.1"
              },
              {
                "fields": [
                  {
                    "items": [
                      {
                        "fields": [
                          {
                            "fields": (v2/*: any*/),
                            "kind": "ObjectValue",
                            "name": "player1"
                          }
                        ],
                        "kind": "ObjectValue",
                        "name": "_or.0"
                      },
                      {
                        "fields": [
                          {
                            "fields": (v2/*: any*/),
                            "kind": "ObjectValue",
                            "name": "player2"
                          }
                        ],
                        "kind": "ObjectValue",
                        "name": "_or.1"
                      }
                    ],
                    "kind": "ListValue",
                    "name": "_or"
                  }
                ],
                "kind": "ObjectValue",
                "name": "_and.2"
              }
            ],
            "kind": "ListValue",
            "name": "_and"
          }
        ],
        "kind": "ObjectValue",
        "name": "where"
      }
    ],
    "concreteType": "resultsConnection",
    "kind": "LinkedField",
    "name": "results_connection",
    "plural": false,
    "selections": [
      {
        "alias": null,
        "args": null,
        "concreteType": "resultsEdge",
        "kind": "LinkedField",
        "name": "edges",
        "plural": true,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "results",
            "kind": "LinkedField",
            "name": "node",
            "plural": false,
            "selections": [
              (v3/*: any*/),
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "player1",
                "plural": false,
                "selections": (v4/*: any*/),
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "player1goals",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "player2",
                "plural": false,
                "selections": (v4/*: any*/),
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "player2goals",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "date",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "extratime",
                "storageKey": null
              }
            ],
            "storageKey": null
          }
        ],
        "storageKey": null
      }
    ],
    "storageKey": null
  }
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "HeadToHeadPageQuery",
    "selections": (v5/*: any*/),
    "type": "query_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "HeadToHeadPageQuery",
    "selections": (v5/*: any*/)
  },
  "params": {
    "cacheID": "8b9f29167e517c3d8f4b5830ca4e433e",
    "id": null,
    "metadata": {},
    "name": "HeadToHeadPageQuery",
    "operationKind": "query",
    "text": "query HeadToHeadPageQuery(\n  $communityName: String!\n  $player1Name: String!\n  $player2Name: String!\n) {\n  results_connection(where: {_and: [{community: {name: {_eq: $communityName}}}, {_or: [{player1: {name: {_eq: $player1Name}}}, {player2: {name: {_eq: $player1Name}}}]}, {_or: [{player1: {name: {_eq: $player2Name}}}, {player2: {name: {_eq: $player2Name}}}]}]}, order_by: {date: desc}) {\n    edges {\n      node {\n        id\n        player1 {\n          id\n          name\n        }\n        player1goals\n        player2 {\n          id\n          name\n        }\n        player2goals\n        date\n        extratime\n      }\n    }\n  }\n}\n"
  }
};
})() |json}
];

include ReasonRelay.MakeLoadQuery({
  type variables = Types.variables;
  type loadedQueryRef = queryRef;
  type response = Types.response;
  let query = node;
  let convertVariables = Internal.convertVariables;
});
