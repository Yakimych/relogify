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
    player1: response_results_connection_edges_node_player1,
    player2: response_results_connection_edges_node_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: string,
    id: string,
    fragmentRefs: ReasonRelay.fragmentRefs([ | `Result_SingleResult]),
  }
  and response_results_connection_edges_node_player1 = {
    id: string,
    name: string,
  }
  and response_results_connection_edges_node_player2 = {
    id: string,
    name: string,
  }
  and response_community_settings_connection = {
    edges: array(response_community_settings_connection_edges),
  }
  and response_community_settings_connection_edges = {
    node: response_community_settings_connection_edges_node,
  }
  and response_community_settings_connection_edges_node = {
    fragmentRefs:
      ReasonRelay.fragmentRefs([ | `ExtraTimeColumn_IncludeExtraTime]),
  };

  type response = {
    results_connection: response_results_connection,
    community_settings_connection: response_community_settings_connection,
  };
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
    {json| {"__root":{"results_connection_edges_node":{"f":""},"community_settings_connection_edges_node":{"f":""}}} |json}
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
v2 = [
  {
    "kind": "Literal",
    "name": "order_by",
    "value": {
      "date": "desc"
    }
  },
  {
    "fields": [
      (v1/*: any*/),
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
v5 = {
  "alias": null,
  "args": null,
  "concreteType": "players",
  "kind": "LinkedField",
  "name": "player1",
  "plural": false,
  "selections": (v4/*: any*/),
  "storageKey": null
},
v6 = {
  "alias": null,
  "args": null,
  "concreteType": "players",
  "kind": "LinkedField",
  "name": "player2",
  "plural": false,
  "selections": (v4/*: any*/),
  "storageKey": null
},
v7 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "player2goals",
  "storageKey": null
},
v8 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "player1goals",
  "storageKey": null
},
v9 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "extratime",
  "storageKey": null
},
v10 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "date",
  "storageKey": null
},
v11 = [
  {
    "fields": [
      (v1/*: any*/)
    ],
    "kind": "ObjectValue",
    "name": "where"
  }
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "ResultsTableQuery",
    "selections": [
      {
        "alias": null,
        "args": (v2/*: any*/),
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
                  (v5/*: any*/),
                  (v6/*: any*/),
                  (v7/*: any*/),
                  (v8/*: any*/),
                  (v9/*: any*/),
                  (v10/*: any*/),
                  (v3/*: any*/),
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "Result_SingleResult"
                  }
                ],
                "storageKey": null
              }
            ],
            "storageKey": null
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v11/*: any*/),
        "concreteType": "community_settingsConnection",
        "kind": "LinkedField",
        "name": "community_settings_connection",
        "plural": false,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "community_settingsEdge",
            "kind": "LinkedField",
            "name": "edges",
            "plural": true,
            "selections": [
              {
                "alias": null,
                "args": null,
                "concreteType": "community_settings",
                "kind": "LinkedField",
                "name": "node",
                "plural": false,
                "selections": [
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "ExtraTimeColumn_IncludeExtraTime"
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
    ],
    "type": "query_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "ResultsTableQuery",
    "selections": [
      {
        "alias": null,
        "args": (v2/*: any*/),
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
                  (v5/*: any*/),
                  (v6/*: any*/),
                  (v7/*: any*/),
                  (v8/*: any*/),
                  (v9/*: any*/),
                  (v10/*: any*/),
                  (v3/*: any*/)
                ],
                "storageKey": null
              }
            ],
            "storageKey": null
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v11/*: any*/),
        "concreteType": "community_settingsConnection",
        "kind": "LinkedField",
        "name": "community_settings_connection",
        "plural": false,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "community_settingsEdge",
            "kind": "LinkedField",
            "name": "edges",
            "plural": true,
            "selections": [
              {
                "alias": null,
                "args": null,
                "concreteType": "community_settings",
                "kind": "LinkedField",
                "name": "node",
                "plural": false,
                "selections": [
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "include_extra_time",
                    "storageKey": null
                  },
                  (v3/*: any*/)
                ],
                "storageKey": null
              }
            ],
            "storageKey": null
          }
        ],
        "storageKey": null
      }
    ]
  },
  "params": {
    "cacheID": "e0d187be6df4387dbf2feeb55c714861",
    "id": null,
    "metadata": {},
    "name": "ResultsTableQuery",
    "operationKind": "query",
    "text": "query ResultsTableQuery(\n  $communityName: String!\n  $dateFrom: timestamptz\n  $dateTo: timestamptz\n) {\n  results_connection(where: {community: {name: {_eq: $communityName}}, date: {_gte: $dateFrom, _lte: $dateTo}}, order_by: {date: desc}) {\n    edges {\n      node {\n        ...Result_SingleResult\n        player1 {\n          id\n          name\n        }\n        player2 {\n          id\n          name\n        }\n        player2goals\n        player1goals\n        extratime\n        date\n        id\n      }\n    }\n  }\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        ...ExtraTimeColumn_IncludeExtraTime\n        id\n      }\n    }\n  }\n}\n\nfragment ExtraTimeColumn_IncludeExtraTime on community_settings {\n  include_extra_time\n}\n\nfragment Result_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n"
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
