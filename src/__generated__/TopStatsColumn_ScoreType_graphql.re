/* @generated */

type enum_score_types_enum = [
  | `Goals
  | `Points
  | `FutureAddedValue(string)
];

let unwrap_enum_score_types_enum: string => enum_score_types_enum =
  fun
  | "Goals" => `Goals
  | "Points" => `Points
  | v => `FutureAddedValue(v);

let wrap_enum_score_types_enum: enum_score_types_enum => string =
  fun
  | `Goals => "Goals"
  | `Points => "Points"
  | `FutureAddedValue(v) => v;

module Types = {
  [@ocaml.warning "-30"];

  type fragment = {
    score_type: [ | `Goals | `Points | `FutureAddedValue(string)],
  };
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"score_type":{"e":"enum_score_types_enum"}}} |json}
  ];
  let fragmentConverterMap = {
    "enum_score_types_enum": unwrap_enum_score_types_enum,
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
  ReasonRelay.fragmentRefs([> | `TopStatsColumn_ScoreType]) => fragmentRef =
  "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "argumentDefinitions": [],
  "kind": "Fragment",
  "metadata": null,
  "name": "TopStatsColumn_ScoreType",
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
