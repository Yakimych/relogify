/* @generated */

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
    player1: response_results_connection_edges_node_player1,
    player2: response_results_connection_edges_node_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: DateTimeUtils.Datetime.t,
    id: string,
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
      ReasonRelay.fragmentRefs(
        [
          | `ResultCommunitySettings_IncludeExtraTime
          | `ResultsTableHeader_CommunitySettings
          | `TopStatsColumn_ScoreType
        ],
      ),
  };

  type response = {
    results_connection: response_results_connection,
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
v3 = {
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
        (v1/*: any*/),
        {
          "alias": null,
          "args": null,
          "kind": "ScalarField",
          "name": "__typename",
          "storageKey": null
        }
      ],
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "cursor",
      "storageKey": null
    }
  ],
  "storageKey": null
},
v4 = {
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
v5 = {
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
v6 = [
  (v5/*: any*/)
],
v7 = [
  {
    "kind": "Literal",
    "name": "first",
    "value": 1000
  },
  {
    "kind": "Literal",
    "name": "order_by",
    "value": {
      "date": "desc"
    }
  },
  (v5/*: any*/)
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "TopBoardQuery",
    "selections": [
      {
        "alias": "results_connection",
        "args": null,
        "concreteType": "resultsConnection",
        "kind": "LinkedField",
        "name": "__TopBoard_query_results_connection_connection",
        "plural": false,
        "selections": [
          (v3/*: any*/),
          (v4/*: any*/),
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
        "args": (v6/*: any*/),
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
                    "name": "ResultCommunitySettings_IncludeExtraTime"
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "ResultsTableHeader_CommunitySettings"
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "TopStatsColumn_ScoreType"
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
    "name": "TopBoardQuery",
    "selections": [
      {
        "alias": null,
        "args": (v7/*: any*/),
        "concreteType": "resultsConnection",
        "kind": "LinkedField",
        "name": "results_connection",
        "plural": false,
        "selections": [
          (v3/*: any*/),
          (v4/*: any*/)
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v7/*: any*/),
        "filters": [],
        "handle": "connection",
        "key": "TopBoard_query_results_connection",
        "kind": "LinkedHandle",
        "name": "results_connection"
      },
      {
        "alias": null,
        "args": (v6/*: any*/),
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
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "score_type",
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
    "cacheID": "cf86669824469cbdb7a4b63c5f4f0775",
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
        }
      ]
    },
    "name": "TopBoardQuery",
    "operationKind": "query",
    "text": "query TopBoardQuery(\n  $communityName: String!\n) {\n  results_connection(first: 1000, where: {community: {name: {_eq: $communityName}}}, order_by: {date: desc}) {\n    ...ResultsTable_Results\n    edges {\n      node {\n        player1 {\n          id\n          name\n        }\n        player2 {\n          id\n          name\n        }\n        player2goals\n        player1goals\n        extratime\n        date\n        id\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      endCursor\n      hasNextPage\n    }\n  }\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        ...ResultCommunitySettings_IncludeExtraTime\n        ...ResultsTableHeader_CommunitySettings\n        ...TopStatsColumn_ScoreType\n        id\n      }\n    }\n  }\n}\n\nfragment ResultCommunitySettings_IncludeExtraTime on community_settings {\n  include_extra_time\n}\n\nfragment Result_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n\nfragment ResultsTableHeader_CommunitySettings on community_settings {\n  score_type\n  include_extra_time\n}\n\nfragment ResultsTable_Results on resultsConnection {\n  edges {\n    node {\n      ...Result_SingleResult\n      player1 {\n        id\n        name\n      }\n      player2 {\n        id\n        name\n      }\n      player2goals\n      player1goals\n      extratime\n      date\n      id\n    }\n  }\n}\n\nfragment TopStatsColumn_ScoreType on community_settings {\n  score_type\n}\n"
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
