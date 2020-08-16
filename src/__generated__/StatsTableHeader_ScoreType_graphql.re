/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

module Types = {
  [@ocaml.warning "-30"];

  type fragment_t = {score_type: enum_score_types_enum};
  type fragment = array(fragment_t);
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
  array(ReasonRelay.fragmentRefs([> | `StatsTableHeader_ScoreType])) =>
  fragmentRef =
  "%identity";

module Utils = {
  external score_types_enum_toString: enum_score_types_enum => string =
    "%identity";
};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "argumentDefinitions": [],
  "kind": "Fragment",
  "metadata": {
    "plural": true
  },
  "name": "StatsTableHeader_ScoreType",
  "selections": [
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "score_type",
      "storageKey": null
    }
  ],
  "type": "community_settings",
  "abstractKey": null
} |json}
];
