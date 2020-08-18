/* @generated */

module Types = {
  [@ocaml.warning "-30"];
  type fragment_edges = {node: fragment_edges_node}
  and fragment_edges_node = {
    id: string,
    fragmentRefs:
      ReasonRelay.fragmentRefs(
        [ | `ResultTableRow_SingleResult | `EditResultTableRow_SingleResult],
      ),
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
  ReasonRelay.fragmentRefs([> | `EditResultsTable_Results]) => fragmentRef =
  "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "argumentDefinitions": [],
  "kind": "Fragment",
  "metadata": null,
  "name": "EditResultsTable_Results",
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
              "kind": "ScalarField",
              "name": "id",
              "storageKey": null
            },
            {
              "args": null,
              "kind": "FragmentSpread",
              "name": "ResultTableRow_SingleResult"
            },
            {
              "args": null,
              "kind": "FragmentSpread",
              "name": "EditResultTableRow_SingleResult"
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
} |json}
];
