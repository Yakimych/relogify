/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

module Types = {
  [@ocaml.warning "-30"];
  type response_community_settings_connection = {
    edges: array(response_community_settings_connection_edges),
  }
  and response_community_settings_connection_edges = {
    node: response_community_settings_connection_edges_node,
  }
  and response_community_settings_connection_edges_node = {
    allow_draws: bool,
    max_selectable_points: int,
    score_type: enum_score_types_enum,
    use_dropdown_for_points: bool,
    include_extra_time: bool,
  };

  type response = {
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
  external score_types_enum_toString: enum_score_types_enum => string =
    "%identity";
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
v1 = [
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
    "name": "where"
  }
],
v2 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "allow_draws",
  "storageKey": null
},
v3 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "max_selectable_points",
  "storageKey": null
},
v4 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "score_type",
  "storageKey": null
},
v5 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "use_dropdown_for_points",
  "storageKey": null
},
v6 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "include_extra_time",
  "storageKey": null
};
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "EditSettingsQuery",
    "selections": [
      {
        "alias": null,
        "args": (v1/*: any*/),
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
                  (v2/*: any*/),
                  (v3/*: any*/),
                  (v4/*: any*/),
                  (v5/*: any*/),
                  (v6/*: any*/)
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
    "name": "EditSettingsQuery",
    "selections": [
      {
        "alias": null,
        "args": (v1/*: any*/),
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
                  (v2/*: any*/),
                  (v3/*: any*/),
                  (v4/*: any*/),
                  (v5/*: any*/),
                  (v6/*: any*/),
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "id",
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
    ]
  },
  "params": {
    "cacheID": "ec3a7c6525800e38b962bd605659c1a5",
    "id": null,
    "metadata": {},
    "name": "EditSettingsQuery",
    "operationKind": "query",
    "text": "query EditSettingsQuery(\n  $communityName: String!\n) {\n  community_settings_connection(where: {community: {name: {_eq: $communityName}}}) {\n    edges {\n      node {\n        allow_draws\n        max_selectable_points\n        score_type\n        use_dropdown_for_points\n        include_extra_time\n        id\n      }\n    }\n  }\n}\n"
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
