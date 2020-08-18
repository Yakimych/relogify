/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

module Types = {
  [@ocaml.warning "-30"];
  type response_update_community_settings = {affected_rows: int};

  type response = {
    update_community_settings: option(response_update_community_settings),
  };
  type rawResponse = response;
  type variables = {
    communityName: string,
    allowDraws: option(bool),
    maxSelectablePoints: option(int),
    scoreType: option(enum_score_types_enum),
    includeExtraTime: option(bool),
    useDropDownForPoints: option(bool),
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"update_community_settings":{"n":""}}} |json}
  ];
  let wrapResponseConverterMap = ();
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"update_community_settings":{"n":""}}} |json}
  ];
  let responseConverterMap = ();
  let convertResponse = v =>
    v
    ->ReasonRelay._convertObj(
        responseConverter,
        responseConverterMap,
        Js.undefined,
      );

  type wrapRawResponseRaw = wrapResponseRaw;
  let convertWrapRawResponse = convertWrapResponse;

  type rawResponseRaw = responseRaw;
  let convertRawResponse = convertResponse;

  let variablesConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"allowDraws":{"n":""},"maxSelectablePoints":{"n":""},"scoreType":{"n":""},"includeExtraTime":{"n":""},"useDropDownForPoints":{"n":""}}} |json}
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

module Utils = {
  external score_types_enum_toString: enum_score_types_enum => string =
    "%identity";
  open Types;
  let makeVariables =
      (
        ~communityName,
        ~allowDraws=?,
        ~maxSelectablePoints=?,
        ~scoreType=?,
        ~includeExtraTime=?,
        ~useDropDownForPoints=?,
        (),
      )
      : variables => {
    communityName,
    allowDraws,
    maxSelectablePoints,
    scoreType,
    includeExtraTime,
    useDropDownForPoints,
  };

  let make_response_update_community_settings =
      (~affected_rows): response_update_community_settings => {
    affected_rows: affected_rows,
  };

  let makeOptimisticResponse = (~update_community_settings=?, ()): rawResponse => {
    update_community_settings: update_community_settings,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "allowDraws"
},
v1 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "communityName"
},
v2 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "includeExtraTime"
},
v3 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "maxSelectablePoints"
},
v4 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "scoreType"
},
v5 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "useDropDownForPoints"
},
v6 = [
  {
    "alias": null,
    "args": [
      {
        "fields": [
          {
            "kind": "Variable",
            "name": "allow_draws",
            "variableName": "allowDraws"
          },
          {
            "kind": "Variable",
            "name": "include_extra_time",
            "variableName": "includeExtraTime"
          },
          {
            "kind": "Variable",
            "name": "max_selectable_points",
            "variableName": "maxSelectablePoints"
          },
          {
            "kind": "Variable",
            "name": "score_type",
            "variableName": "scoreType"
          },
          {
            "kind": "Variable",
            "name": "use_dropdown_for_points",
            "variableName": "useDropDownForPoints"
          }
        ],
        "kind": "ObjectValue",
        "name": "_set"
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
          }
        ],
        "kind": "ObjectValue",
        "name": "where"
      }
    ],
    "concreteType": "community_settings_mutation_response",
    "kind": "LinkedField",
    "name": "update_community_settings",
    "plural": false,
    "selections": [
      {
        "alias": null,
        "args": null,
        "kind": "ScalarField",
        "name": "affected_rows",
        "storageKey": null
      }
    ],
    "storageKey": null
  }
];
return {
  "fragment": {
    "argumentDefinitions": [
      (v0/*: any*/),
      (v1/*: any*/),
      (v2/*: any*/),
      (v3/*: any*/),
      (v4/*: any*/),
      (v5/*: any*/)
    ],
    "kind": "Fragment",
    "metadata": null,
    "name": "EditSettings_UpdateCommunitySettings_Mutation",
    "selections": (v6/*: any*/),
    "type": "mutation_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": [
      (v1/*: any*/),
      (v0/*: any*/),
      (v3/*: any*/),
      (v4/*: any*/),
      (v2/*: any*/),
      (v5/*: any*/)
    ],
    "kind": "Operation",
    "name": "EditSettings_UpdateCommunitySettings_Mutation",
    "selections": (v6/*: any*/)
  },
  "params": {
    "cacheID": "9979923fb43b16c4ec14511e6f9e5c5b",
    "id": null,
    "metadata": {},
    "name": "EditSettings_UpdateCommunitySettings_Mutation",
    "operationKind": "mutation",
    "text": "mutation EditSettings_UpdateCommunitySettings_Mutation(\n  $communityName: String!\n  $allowDraws: Boolean\n  $maxSelectablePoints: Int\n  $scoreType: score_types_enum\n  $includeExtraTime: Boolean\n  $useDropDownForPoints: Boolean\n) {\n  update_community_settings(where: {community: {name: {_eq: $communityName}}}, _set: {allow_draws: $allowDraws, max_selectable_points: $maxSelectablePoints, score_type: $scoreType, include_extra_time: $includeExtraTime, use_dropdown_for_points: $useDropDownForPoints}) {\n    affected_rows\n  }\n}\n"
  }
};
})() |json}
];
