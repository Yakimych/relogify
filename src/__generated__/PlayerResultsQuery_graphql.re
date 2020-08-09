/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

module Types = {
  [@ocaml.warning "-30"];
  type response_results_connection = {
    edges: array(response_results_connection_edges),
    fragmentRefs: ReasonRelay.fragmentRefs([ | `ResultsTable_Results]),
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
    date: DateTimeUtils.Datetime.t,
    extratime: bool,
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
    score_type: enum_score_types_enum,
    fragmentRefs:
      ReasonRelay.fragmentRefs(
        [
          | `ExtraTimeColumn_IncludeExtraTime
          | `ResultsTableHeader_CommunitySettings
        ],
      ),
  };

  type response = {
    results_connection: response_results_connection,
    community_settings_connection: response_community_settings_connection,
  };
  type rawResponse = response;
  type refetchVariables = {
    communityName: option(string),
    playerName: option(string),
  };
  let makeRefetchVariables =
      (~communityName=?, ~playerName=?, ()): refetchVariables => {
    communityName,
    playerName,
  };
  type variables = {
    communityName: string,
    playerName: string,
  };
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"results_connection_edges_node_date":{"c":"DateTimeUtils.Datetime"},"results_connection":{"f":""},"community_settings_connection_edges_node":{"f":""}}} |json}
  ];
  let responseConverterMap = {
    "DateTimeUtils.Datetime": DateTimeUtils.Datetime.parse,
  };
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
  external score_types_enum_toString: enum_score_types_enum => string =
    "%identity";
  open Types;
  let makeVariables = (~communityName, ~playerName): variables => {
    communityName,
    playerName,
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
    "name": "playerName"
  }
],
v1 = [
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
v2 = [
  {
    "fields": [
      {
        "kind": "Variable",
        "name": "_eq",
        "variableName": "playerName"
      }
    ],
    "kind": "ObjectValue",
    "name": "name"
  }
],
v3 = [
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
            "fields": (v1/*: any*/),
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
            "name": "_and.1"
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
v4 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v5 = [
  (v4/*: any*/),
  {
    "alias": null,
    "args": null,
    "kind": "ScalarField",
    "name": "name",
    "storageKey": null
  }
],
v6 = {
  "alias": null,
  "args": null,
  "concreteType": "players",
  "kind": "LinkedField",
  "name": "player1",
  "plural": false,
  "selections": (v5/*: any*/),
  "storageKey": null
},
v7 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "player1goals",
  "storageKey": null
},
v8 = {
  "alias": null,
  "args": null,
  "concreteType": "players",
  "kind": "LinkedField",
  "name": "player2",
  "plural": false,
  "selections": (v5/*: any*/),
  "storageKey": null
},
v9 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "player2goals",
  "storageKey": null
},
v10 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "date",
  "storageKey": null
},
v11 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "extratime",
  "storageKey": null
},
v12 = [
  {
    "fields": (v1/*: any*/),
    "kind": "ObjectValue",
    "name": "where"
  }
],
v13 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "score_type",
  "storageKey": null
};
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "PlayerResultsQuery",
    "selections": [
      {
        "alias": null,
        "args": (v3/*: any*/),
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
                  (v4/*: any*/),
                  (v6/*: any*/),
                  (v7/*: any*/),
                  (v8/*: any*/),
                  (v9/*: any*/),
                  (v10/*: any*/),
                  (v11/*: any*/)
                ],
                "storageKey": null
              }
            ],
            "storageKey": null
          },
          {
            "args": null,
            "kind": "FragmentSpread",
            "name": "ResultsTable_Results"
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v12/*: any*/),
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
                  (v13/*: any*/),
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "ExtraTimeColumn_IncludeExtraTime"
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "ResultsTableHeader_CommunitySettings"
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
    "name": "PlayerResultsQuery",
    "selections": [
      {
        "alias": null,
        "args": (v3/*: any*/),
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
                  (v6/*: any*/),
                  (v8/*: any*/),
                  (v9/*: any*/),
                  (v7/*: any*/),
                  (v11/*: any*/),
                  (v10/*: any*/),
                  (v4/*: any*/)
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
        "args": (v12/*: any*/),
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
                  (v13/*: any*/),
                  (v4/*: any*/)
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
    "cacheID": "3600e28620ce85c81b1c579367d19800",
    "id": null,
    "metadata": {},
    "name": "PlayerResultsQuery",
    "operationKind": "query",
    "text": "query PlayerResultsQuery(\n  $communityName: String!\n  $playerName: String!\n) {\n  results_connection(where: {_and: [{community: {name: {_eq: $communityName}}}, {_or: [{player1: {name: {_eq: $playerName}}}, {player2: {name: {_eq: $playerName}}}]}]}, order_by: {date: desc}) {\n    ...ResultsTable_Results\n    edges {\n      node {\n        id\n        player1 {\n          id\n          name\n        }\n        player1goals\n        player2 {\n          id\n          name\n        }\n        player2goals\n        date\n        extratime\n      }\n    }\n  }\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        ...ExtraTimeColumn_IncludeExtraTime\n        ...ResultsTableHeader_CommunitySettings\n        score_type\n        id\n      }\n    }\n  }\n}\n\nfragment ExtraTimeColumn_IncludeExtraTime on community_settings {\n  include_extra_time\n}\n\nfragment Result_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n\nfragment ResultsTableHeader_CommunitySettings on community_settings {\n  score_type\n  include_extra_time\n}\n\nfragment ResultsTable_Results on resultsConnection {\n  edges {\n    node {\n      ...Result_SingleResult\n      player1 {\n        id\n        name\n      }\n      player2 {\n        id\n        name\n      }\n      player2goals\n      player1goals\n      extratime\n      date\n      id\n    }\n  }\n}\n"
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
