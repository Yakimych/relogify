/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type response_results_connection = {
    edges: array(response_results_connection_edges),
    fragmentRefs: ReasonRelay.fragmentRefs([ | `EditResultsFragment]),
  }
  and response_results_connection_edges = {
    node: response_results_connection_edges_node,
  }
  and response_results_connection_edges_node = {id: string}
  and response_players_connection = {
    edges: array(response_players_connection_edges),
    fragmentRefs:
      ReasonRelay.fragmentRefs(
        [ | `PlayerPicker_Players | `ExistingPlayerPicker_Players],
      ),
  }
  and response_players_connection_edges = {
    node: response_players_connection_edges_node,
  }
  and response_players_connection_edges_node = {id: string}
  and response_community_settings_connection = {
    edges: array(response_community_settings_connection_edges),
  }
  and response_community_settings_connection_edges = {
    node: response_community_settings_connection_edges_node,
  }
  and response_community_settings_connection_edges_node = {
    fragmentRefs:
      ReasonRelay.fragmentRefs(
        [
          | `AddResultTableRowFragment_CommunitySettings
          | `EditResultTableRowFragment_CommunitySettings
        ],
      ),
  };

  type response = {
    results_connection: response_results_connection,
    players_connection: response_players_connection,
    community_settings_connection: response_community_settings_connection,
  };
  type rawResponse = response;
  type refetchVariables = {communityName: option(string)};
  let makeRefetchVariables = (~communityName=?, ()): refetchVariables => {
    communityName: communityName,
  };
  type variables = {communityName: string};
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"results_connection":{"f":""},"players_connection":{"f":""},"community_settings_connection_edges_node":{"f":""}}} |json}
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
  let makeVariables = (~communityName): variables => {
    communityName: communityName,
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
  }
],
v1 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v2 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "__typename",
  "storageKey": null
},
v3 = [
  (v1/*: any*/),
  (v2/*: any*/)
],
v4 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "cursor",
  "storageKey": null
},
v5 = {
  "alias": null,
  "args": null,
  "concreteType": "PageInfo",
  "kind": "LinkedField",
  "name": "pageInfo",
  "plural": false,
  "selections": [
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "endCursor",
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "hasNextPage",
      "storageKey": null
    }
  ],
  "storageKey": null
},
v6 = {
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
  "name": "where"
},
v7 = [
  (v6/*: any*/)
],
v8 = {
  "kind": "Literal",
  "name": "first",
  "value": 1000
},
v9 = [
  (v8/*: any*/),
  {
    "kind": "Literal",
    "name": "order_by",
    "value": {
      "date": "desc"
    }
  },
  (v6/*: any*/)
],
v10 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "name",
  "storageKey": null
},
v11 = [
  (v1/*: any*/),
  (v10/*: any*/)
],
v12 = [
  (v8/*: any*/),
  (v6/*: any*/)
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "CommunityAdminPageQuery",
    "selections": [
      {
        "alias": "results_connection",
        "args": null,
        "concreteType": "resultsConnection",
        "kind": "LinkedField",
        "name": "__EditResults_query_results_connection_connection",
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
                "selections": (v3/*: any*/),
                "storageKey": null
              },
              (v4/*: any*/)
            ],
            "storageKey": null
          },
          (v5/*: any*/),
          {
            "args": null,
            "kind": "FragmentSpread",
            "name": "EditResultsFragment"
          }
        ],
        "storageKey": null
      },
      {
        "alias": "players_connection",
        "args": null,
        "concreteType": "playersConnection",
        "kind": "LinkedField",
        "name": "__EditResults_query_players_connection_connection",
        "plural": false,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "playersEdge",
            "kind": "LinkedField",
            "name": "edges",
            "plural": true,
            "selections": [
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "node",
                "plural": false,
                "selections": (v3/*: any*/),
                "storageKey": null
              },
              (v4/*: any*/)
            ],
            "storageKey": null
          },
          (v5/*: any*/),
          {
            "args": null,
            "kind": "FragmentSpread",
            "name": "PlayerPicker_Players"
          },
          {
            "args": null,
            "kind": "FragmentSpread",
            "name": "ExistingPlayerPicker_Players"
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v7/*: any*/),
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
                    "name": "AddResultTableRowFragment_CommunitySettings"
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "EditResultTableRowFragment_CommunitySettings"
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
    "name": "CommunityAdminPageQuery",
    "selections": [
      {
        "alias": null,
        "args": (v9/*: any*/),
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
                    "selections": (v11/*: any*/),
                    "storageKey": null
                  },
                  {
                    "alias": null,
                    "args": null,
                    "concreteType": "players",
                    "kind": "LinkedField",
                    "name": "player2",
                    "plural": false,
                    "selections": (v11/*: any*/),
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
                  (v1/*: any*/),
                  (v2/*: any*/)
                ],
                "storageKey": null
              },
              (v4/*: any*/)
            ],
            "storageKey": null
          },
          (v5/*: any*/)
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v9/*: any*/),
        "filters": [],
        "handle": "connection",
        "key": "EditResults_query_results_connection",
        "kind": "LinkedHandle",
        "name": "results_connection"
      },
      {
        "alias": null,
        "args": (v12/*: any*/),
        "concreteType": "playersConnection",
        "kind": "LinkedField",
        "name": "players_connection",
        "plural": false,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "playersEdge",
            "kind": "LinkedField",
            "name": "edges",
            "plural": true,
            "selections": [
              {
                "alias": null,
                "args": null,
                "concreteType": "players",
                "kind": "LinkedField",
                "name": "node",
                "plural": false,
                "selections": [
                  (v10/*: any*/),
                  (v1/*: any*/),
                  (v2/*: any*/)
                ],
                "storageKey": null
              },
              (v4/*: any*/)
            ],
            "storageKey": null
          },
          (v5/*: any*/)
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v12/*: any*/),
        "filters": [],
        "handle": "connection",
        "key": "EditResults_query_players_connection",
        "kind": "LinkedHandle",
        "name": "players_connection"
      },
      {
        "alias": null,
        "args": (v7/*: any*/),
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
                    "name": "score_type",
                    "storageKey": null
                  },
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "max_selectable_points",
                    "storageKey": null
                  },
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "allow_draws",
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
    ]
  },
  "params": {
    "cacheID": "7d6a1238e8529f1374da843beea07f3d",
    "id": null,
    "metadata": {
      "connection": [
        {
          "count": null,
          "cursor": null,
          "direction": "forward",
          "path": [
            "results_connection"
          ]
        },
        {
          "count": null,
          "cursor": null,
          "direction": "forward",
          "path": [
            "players_connection"
          ]
        }
      ]
    },
    "name": "CommunityAdminPageQuery",
    "operationKind": "query",
    "text": "query CommunityAdminPageQuery(\n  $communityName: String!\n) {\n  results_connection(first: 1000, where: {community: {name: {_eq: $communityName}}}, order_by: {date: desc}) {\n    ...EditResultsFragment\n    edges {\n      node {\n        id\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      endCursor\n      hasNextPage\n    }\n  }\n  players_connection(first: 1000, where: {community: {name: {_eq: $communityName}}}) {\n    ...PlayerPicker_Players\n    ...ExistingPlayerPicker_Players\n    edges {\n      node {\n        id\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      endCursor\n      hasNextPage\n    }\n  }\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        ...AddResultTableRowFragment_CommunitySettings\n        ...EditResultTableRowFragment_CommunitySettings\n        id\n      }\n    }\n  }\n}\n\nfragment AddResultTableRowFragment_CommunitySettings on community_settings {\n  score_type\n  max_selectable_points\n  allow_draws\n}\n\nfragment EditResultTableRowFragment_CommunitySettings on community_settings {\n  score_type\n  max_selectable_points\n}\n\nfragment EditResultTableRow_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n\nfragment EditResultsFragment on resultsConnection {\n  ...EditResultsTable_Results\n  edges {\n    node {\n      id\n    }\n  }\n}\n\nfragment EditResultsTable_Results on resultsConnection {\n  edges {\n    node {\n      ...ResultTableRow_SingleResult\n      ...EditResultTableRow_SingleResult\n      id\n    }\n  }\n}\n\nfragment ExistingPlayerPicker_Players on playersConnection {\n  edges {\n    node {\n      id\n      name\n    }\n  }\n}\n\nfragment PlayerPicker_Players on playersConnection {\n  edges {\n    node {\n      name\n      id\n    }\n  }\n}\n\nfragment ResultTableRow_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n"
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
