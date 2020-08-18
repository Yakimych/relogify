/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type fragment_player1 = {
    id: string,
    name: string,
  }
  and fragment_player2 = {
    id: string,
    name: string,
  };

  type fragment = {
    player1: fragment_player1,
    player2: fragment_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: DateTimeUtils.Datetime.t,
    id: string,
  };
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"date":{"c":"DateTimeUtils.Datetime"}}} |json}
  ];
  let fragmentConverterMap = {
    "DateTimeUtils.Datetime": DateTimeUtils.Datetime.parse,
  };
  let convertFragment = v =>
    v
    ->ReasonRelay._convertObj(
        fragmentConverter,
        fragmentConverterMap,
        Js.undefined,
      );
};

type t;
type fragmentRef;
external getFragmentRef:
  ReasonRelay.fragmentRefs([> | `ResultTableRow_SingleResult]) => fragmentRef =
  "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v1 = [
  (v0/*: any*/),
  {
    "alias": null,
    "args": null,
    "kind": "ScalarField",
    "name": "name",
    "storageKey": null
  }
];
return {
  "argumentDefinitions": [],
  "kind": "Fragment",
  "metadata": null,
  "name": "ResultTableRow_SingleResult",
  "selections": [
    {
      "alias": null,
      "args": null,
      "concreteType": "players",
      "kind": "LinkedField",
      "name": "player1",
      "plural": false,
      "selections": (v1/*: any*/),
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "concreteType": "players",
      "kind": "LinkedField",
      "name": "player2",
      "plural": false,
      "selections": (v1/*: any*/),
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
    (v0/*: any*/)
  ],
  "type": "results",
  "abstractKey": null
};
})() |json}
];
