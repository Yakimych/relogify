/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

module Types = {
  [@ocaml.warning "-30"];

  type fragment_t = {
    allow_draws: bool,
    max_selectable_points: int,
    score_type: enum_score_types_enum,
    use_dropdown_for_points: bool,
    include_extra_time: bool,
  };
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
  array(
    ReasonRelay.fragmentRefs([> | `EditSettingsFragment_CommunitySettings]),
  ) =>
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
  "name": "EditSettingsFragment_CommunitySettings",
  "selections": [
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "allow_draws",
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "max_selectable_points",
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "score_type",
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "use_dropdown_for_points",
      "storageKey": null
    },
    {
      "alias": null,
      "args": null,
      "kind": "ScalarField",
      "name": "include_extra_time",
      "storageKey": null
    }
  ],
  "type": "community_settings",
  "abstractKey": null
} |json}
];
