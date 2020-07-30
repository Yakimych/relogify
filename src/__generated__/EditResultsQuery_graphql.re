/* @generated */

module Types = {
  type response_results_connection_edges_node_player2 = {
    id: string,
    name: string,
  };
  type response_results_connection_edges_node_player1 = {
    id: string,
    name: string,
  };
  type response_results_connection_edges_node = {
    player1: response_results_connection_edges_node_player1,
    player2: response_results_connection_edges_node_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: string,
    id: string,
  };
  type response_results_connection_edges = {
    node: response_results_connection_edges_node,
  };
  type response_results_connection = {
    edges: array(response_results_connection_edges),
  };

  type response = {results_connection: response_results_connection};
  type rawResponse = response;
  type refetchVariables = {
    communityName: option(string),
    dateFrom: option(string),
    dateTo: option(string),
  };
  let makeRefetchVariables =
      (~communityName=?, ~dateFrom=?, ~dateTo=?, ()): refetchVariables => {
    communityName,
    dateFrom,
    dateTo,
  };
  type variables = {
    communityName: string,
    dateFrom: option(string),
    dateTo: option(string),
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
    {json| {"__root":{"dateFrom":{"n":""},"dateTo":{"n":""}}} |json}
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
  let makeVariables = (~communityName, ~dateFrom=?, ~dateTo=?, ()): variables => {
    communityName,
    dateFrom,
    dateTo,
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
    "name": "dateFrom"
  },
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "dateTo"
  }
],
v1 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v2 = [
  (v1/*: any*/),
  {
    "alias": null,
    "args": null,
    "kind": "ScalarField",
    "name": "name",
    "storageKey": null
  }
],
v3 = [
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
          },
          {
            "fields": [
              {
                "kind": "Variable",
                "name": "_gte",
                "variableName": "dateFrom"
              },
              {
                "kind": "Variable",
                "name": "_lte",
                "variableName": "dateTo"
              }
            ],
            "kind": "ObjectValue",
            "name": "date"
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
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "player1",
                "plural": false,
                "selections": (v2/*: any*/),
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "player2",
                "plural": false,
                "selections": (v2/*: any*/),
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
                "name": "player1goals",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "extratime",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "date",
                "storageKey": null
              },
              (v1/*: any*/)
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
    "name": "EditResultsQuery",
    "selections": (v3/*: any*/),
    "type": "query_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "EditResultsQuery",
    "selections": (v3/*: any*/)
  },
  "params": {
    "cacheID": "5cb9154e420d511fa34259c36cabf087",
    "id": null,
    "metadata": {},
    "name": "EditResultsQuery",
    "operationKind": "query",
    "text": "query EditResultsQuery(\n  $communityName: String!\n  $dateFrom: timestamptz\n  $dateTo: timestamptz\n) {\n  results_connection(where: {community: {name: {_eq: $communityName}}, date: {_gte: $dateFrom, _lte: $dateTo}}, order_by: {date: desc}) {\n    edges {\n      node {\n        player1 {\n          id\n          name\n        }\n        player2 {\n          id\n          name\n        }\n        player2goals\n        player1goals\n        extratime\n        date\n        id\n      }\n    }\n  }\n}\n"
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
