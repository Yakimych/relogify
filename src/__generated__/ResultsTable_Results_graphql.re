/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type fragment_edges = {node: fragment_edges_node}
  and fragment_edges_node = {
    player1: fragment_edges_node_player1,
    player2: fragment_edges_node_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: string,
    id: string,
    fragmentRefs: ReasonRelay.fragmentRefs([ | `Result_SingleResult]),
  }
  and fragment_edges_node_player1 = {
    id: string,
    name: string,
  }
  and fragment_edges_node_player2 = {
    id: string,
    name: string,
  };

  type fragment = {edges: array(fragment_edges)};
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"edges_node":{"f":""}}} |json}
  ];
  let fragmentConverterMap = ();
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
  ReasonRelay.fragmentRefs([> | `ResultsTable_Results]) => fragmentRef =
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
  "name": "ResultsTable_Results",
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
            (v0/*: any*/),
            {
              "args": null,
              "kind": "FragmentSpread",
              "name": "Result_SingleResult"
            }
          ],
          "storageKey": null
        }
      ],
      "storageKey": null
    }
  ],
  "type": "resultsConnection",
  "abstractKey": null
};
})() |json}
];
