/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type response_delete_results = {affected_rows: int};

  type response = {delete_results: option(response_delete_results)};
  type rawResponse = response;
  type variables = {resultId: int};
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"delete_results":{"n":""}}} |json}
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
    {json| {"__root":{"delete_results":{"n":""}}} |json}
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
  let makeVariables = (~resultId): variables => {resultId: resultId};

  let make_response_delete_results = (~affected_rows): response_delete_results => {
    affected_rows: affected_rows,
  };

  let makeOptimisticResponse = (~delete_results=?, ()): rawResponse => {
    delete_results: delete_results,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "resultId"
  }
],
v1 = [
  {
    "alias": null,
    "args": [
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
    "name": "delete_results",
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
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "EditResultsTable_DeleteResult_Mutation",
    "selections": (v1/*: any*/),
    "type": "mutation_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "EditResultsTable_DeleteResult_Mutation",
    "selections": (v1/*: any*/)
  },
  "params": {
    "cacheID": "d44734674814dec8312260be1c981f11",
    "id": null,
    "metadata": {},
    "name": "EditResultsTable_DeleteResult_Mutation",
    "operationKind": "mutation",
    "text": "mutation EditResultsTable_DeleteResult_Mutation(\n  $resultId: Int!\n) {\n  delete_results(where: {id: {_eq: $resultId}}) {\n    affected_rows\n  }\n}\n"
  }
};
})() |json}
];
