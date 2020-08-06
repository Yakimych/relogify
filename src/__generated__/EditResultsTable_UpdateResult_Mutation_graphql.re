/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type response_update_results = {affected_rows: int};

  type response = {update_results: option(response_update_results)};
  type rawResponse = response;
  type variables = {
    resultId: int,
    player1Id: int,
    player2Id: int,
    player1Goals: int,
    player2Goals: int,
    extraTime: bool,
    date: string,
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"update_results":{"n":""}}} |json}
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
    {json| {"__root":{"update_results":{"n":""}}} |json}
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

module Utils = {
  open Types;
  let makeVariables =
      (
        ~resultId,
        ~player1Id,
        ~player2Id,
        ~player1Goals,
        ~player2Goals,
        ~extraTime,
        ~date,
      )
      : variables => {
    resultId,
    player1Id,
    player2Id,
    player1Goals,
    player2Goals,
    extraTime,
    date,
  };

  let make_response_update_results = (~affected_rows): response_update_results => {
    affected_rows: affected_rows,
  };

  let makeOptimisticResponse = (~update_results=?, ()): rawResponse => {
    update_results: update_results,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "date"
},
v1 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "extraTime"
},
v2 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "player1Goals"
},
v3 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "player1Id"
},
v4 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "player2Goals"
},
v5 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "player2Id"
},
v6 = {
  "defaultValue": null,
  "kind": "LocalArgument",
  "name": "resultId"
},
v7 = [
  {
    "alias": null,
    "args": [
      {
        "fields": [
          {
            "kind": "Variable",
            "name": "date",
            "variableName": "date"
          },
          {
            "kind": "Variable",
            "name": "extratime",
            "variableName": "extraTime"
          },
          {
            "kind": "Variable",
            "name": "player1Id",
            "variableName": "player1Id"
          },
          {
            "kind": "Variable",
            "name": "player1goals",
            "variableName": "player1Goals"
          },
          {
            "kind": "Variable",
            "name": "player2Id",
            "variableName": "player2Id"
          },
          {
            "kind": "Variable",
            "name": "player2goals",
            "variableName": "player2Goals"
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
                "kind": "Variable",
                "name": "_eq",
                "variableName": "resultId"
              }
            ],
            "kind": "ObjectValue",
            "name": "id"
          }
        ],
        "kind": "ObjectValue",
        "name": "where"
      }
    ],
    "concreteType": "results_mutation_response",
    "kind": "LinkedField",
    "name": "update_results",
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
      (v5/*: any*/),
      (v6/*: any*/)
    ],
    "kind": "Fragment",
    "metadata": null,
    "name": "EditResultsTable_UpdateResult_Mutation",
    "selections": (v7/*: any*/),
    "type": "mutation_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": [
      (v6/*: any*/),
      (v3/*: any*/),
      (v5/*: any*/),
      (v2/*: any*/),
      (v4/*: any*/),
      (v1/*: any*/),
      (v0/*: any*/)
    ],
    "kind": "Operation",
    "name": "EditResultsTable_UpdateResult_Mutation",
    "selections": (v7/*: any*/)
  },
  "params": {
    "cacheID": "d00496fb08b251abb372d9072a127c8a",
    "id": null,
    "metadata": {},
    "name": "EditResultsTable_UpdateResult_Mutation",
    "operationKind": "mutation",
    "text": "mutation EditResultsTable_UpdateResult_Mutation(\n  $resultId: Int!\n  $player1Id: Int!\n  $player2Id: Int!\n  $player1Goals: Int!\n  $player2Goals: Int!\n  $extraTime: Boolean!\n  $date: timestamptz!\n) {\n  update_results(where: {id: {_eq: $resultId}}, _set: {player1Id: $player1Id, player1goals: $player1Goals, player2goals: $player2Goals, player2Id: $player2Id, extratime: $extraTime, date: $date}) {\n    affected_rows\n  }\n}\n"
  }
};
})() |json}
];
