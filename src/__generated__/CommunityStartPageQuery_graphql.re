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
  and response_results_connection_edges_node = {id: string}
  and response_players_connection = {
    fragmentRefs: ReasonRelay.fragmentRefs([ | `PlayerPicker_Players]),
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
          | `ExtraTimeColumn_IncludeExtraTime
          | `ResultsTableHeader_CommunitySettings
          | `AddResultFragment_CommunitySettings
        ],
      ),
  };

  type response = {
    results_connection: response_results_connection,
    players_connection: response_players_connection,
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
  {
    "fields": [
      (v1/*: any*/)
    ],
    "kind": "ObjectValue",
    "name": "where"
  }
],
v5 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "name",
  "storageKey": null
},
v6 = [
  (v3/*: any*/),
  (v5/*: any*/)
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "CommunityStartPageQuery",
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
                  (v3/*: any*/)
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
        "args": (v4/*: any*/),
        "concreteType": "playersConnection",
        "kind": "LinkedField",
        "name": "players_connection",
        "plural": false,
        "selections": [
          {
            "args": null,
            "kind": "FragmentSpread",
            "name": "PlayerPicker_Players"
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v4/*: any*/),
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
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "ResultsTableHeader_CommunitySettings"
                  },
                  {
                    "args": null,
                    "kind": "FragmentSpread",
                    "name": "AddResultFragment_CommunitySettings"
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
    "name": "CommunityStartPageQuery",
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
                  {
                    "alias": null,
                    "args": null,
                    "concreteType": "players",
                    "kind": "LinkedField",
                    "name": "player1",
                    "plural": false,
                    "selections": (v6/*: any*/),
                    "storageKey": null
                  },
                  {
                    "alias": null,
                    "args": null,
                    "concreteType": "players",
                    "kind": "LinkedField",
                    "name": "player2",
                    "plural": false,
                    "selections": (v6/*: any*/),
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
        "args": (v4/*: any*/),
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
                  (v5/*: any*/),
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
        "args": (v4/*: any*/),
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
    "cacheID": "3a703486d61c60c0157c17a0f3dcde2e",
    "id": null,
    "metadata": {},
    "name": "CommunityStartPageQuery",
    "operationKind": "query",
    "text": "query CommunityStartPageQuery(\n  $communityName: String!\n  $dateFrom: timestamptz\n  $dateTo: timestamptz\n) {\n  results_connection(where: {community: {name: {_eq: $communityName}}, date: {_gte: $dateFrom, _lte: $dateTo}}, order_by: {date: desc}) {\n    ...ResultsTable_Results\n    edges {\n      node {\n        id\n      }\n    }\n  }\n  players_connection(where: {community: {name: {_eq: $communityName}}}) {\n    ...PlayerPicker_Players\n  }\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        ...ExtraTimeColumn_IncludeExtraTime\n        ...ResultsTableHeader_CommunitySettings\n        ...AddResultFragment_CommunitySettings\n        id\n      }\n    }\n  }\n}\n\nfragment AddResultFragment_CommunitySettings on community_settings {\n  include_extra_time\n  score_type\n  max_selectable_points\n  allow_draws\n}\n\nfragment ExtraTimeColumn_IncludeExtraTime on community_settings {\n  include_extra_time\n}\n\nfragment PlayerPicker_Players on playersConnection {\n  edges {\n    node {\n      name\n      id\n    }\n  }\n}\n\nfragment Result_SingleResult on results {\n  player1 {\n    id\n    name\n  }\n  player2 {\n    id\n    name\n  }\n  player2goals\n  player1goals\n  extratime\n  date\n  id\n}\n\nfragment ResultsTableHeader_CommunitySettings on community_settings {\n  score_type\n  include_extra_time\n}\n\nfragment ResultsTable_Results on resultsConnection {\n  edges {\n    node {\n      ...Result_SingleResult\n      player1 {\n        id\n        name\n      }\n      player2 {\n        id\n        name\n      }\n      player2goals\n      player1goals\n      extratime\n      date\n      id\n    }\n  }\n}\n"
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
