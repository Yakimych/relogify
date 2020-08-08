/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type response_delete_results_by_pk = {id: string};

  type response = {
    delete_results_by_pk: option(response_delete_results_by_pk),
  };
  type rawResponse = response;
  type variables = {resultId: int};
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"delete_results_by_pk":{"n":""}}} |json}
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
    {json| {"__root":{"delete_results_by_pk":{"n":""}}} |json}
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

  let make_response_delete_results_by_pk =
      (~id): response_delete_results_by_pk => {
    id: id,
  };

  let makeOptimisticResponse = (~delete_results_by_pk=?, ()): rawResponse => {
    delete_results_by_pk: delete_results_by_pk,
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
        "kind": "Variable",
        "name": "id",
        "variableName": "resultId"
      }
    ],
    "concreteType": "results",
    "kind": "LinkedField",
    "name": "delete_results_by_pk",
    "plural": false,
    "selections": [
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
    "cacheID": "e4a0706d361acc9e0a81c12bdec4bf26",
    "id": null,
    "metadata": {},
    "name": "EditResultsTable_DeleteResult_Mutation",
    "operationKind": "mutation",
    "text": "mutation EditResultsTable_DeleteResult_Mutation(\n  $resultId: Int!\n) {\n  delete_results_by_pk(id: $resultId) {\n    id\n  }\n}\n"
  }
};
})() |json}
];
