/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type fragment_edges = {node: fragment_edges_node}
  and fragment_edges_node = {name: string};

  type fragment = {edges: array(fragment_edges)};
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {} |json}
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
  ReasonRelay.fragmentRefs([> | `PlayerPicker_Players]) => fragmentRef =
  "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "argumentDefinitions": [],
  "kind": "Fragment",
  "metadata": null,
  "name": "PlayerPicker_Players",
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
            {
              "alias": null,
              "args": null,
              "kind": "ScalarField",
              "name": "name",
              "storageKey": null
            }
          ],
          "storageKey": null
        }
      ],
      "storageKey": null
    }
  ],
  "type": "playersConnection",
  "abstractKey": null
} |json}
];
