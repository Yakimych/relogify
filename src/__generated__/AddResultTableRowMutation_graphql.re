/* @generated */

type enum_score_types_enum = pri [> | `Goals | `Points];

type enum_results_update_column =
  pri [>
    | `comment
    | `communityId
    | `date
    | `extratime
    | `id
    | `player1Id
    | `player1goals
    | `player2Id
    | `player2goals
  ];

type enum_results_constraint = pri [> | `results_pkey];

type enum_players_update_column = pri [> | `communityId | `id | `name];

type enum_players_constraint =
  pri [> | `players_name_communityId_key | `players_pkey];

type enum_community_settings_update_column =
  pri [>
    | `allow_draws
    | `community_id
    | `include_extra_time
    | `max_selectable_points
    | `score_type
    | `use_dropdown_for_points
  ];

type enum_community_settings_constraint = pri [> | `community_settings_pkey];

type enum_communities_update_column = pri [> | `description | `id | `name];

type enum_communities_constraint =
  pri [> | `communities_name_key | `communities_pkey];

module Types = {
  [@ocaml.warning "-30"];
  type response_insert_results_one = {
    player1: response_insert_results_one_player1,
    player2: response_insert_results_one_player2,
    player2goals: int,
    player1goals: int,
    extratime: bool,
    date: DateTimeUtils.Datetime.t,
    id: string,
  }
  and response_insert_results_one_player1 = {
    id: string,
    name: string,
  }
  and response_insert_results_one_player2 = {
    id: string,
    name: string,
  }
  and results_insert_input = {
    comment: option(string),
    community: option(communities_obj_rel_insert_input),
    communityId: option(int),
    date: option(DateTimeUtils.Datetime.t),
    extratime: option(bool),
    id: option(int),
    player1: option(players_obj_rel_insert_input),
    player1Id: option(int),
    player1goals: option(int),
    player2: option(players_obj_rel_insert_input),
    player2Id: option(int),
    player2goals: option(int),
  }
  and communities_obj_rel_insert_input = {
    data: communities_insert_input,
    on_conflict: option(communities_on_conflict),
  }
  and communities_insert_input = {
    community_settings: option(community_settings_arr_rel_insert_input),
    description: option(string),
    id: option(int),
    name: option(string),
    players: option(players_arr_rel_insert_input),
    results: option(results_arr_rel_insert_input),
  }
  and community_settings_arr_rel_insert_input = {
    data: array(community_settings_insert_input),
    on_conflict: option(community_settings_on_conflict),
  }
  and community_settings_insert_input = {
    allow_draws: option(bool),
    community: option(communities_obj_rel_insert_input),
    community_id: option(int),
    include_extra_time: option(bool),
    max_selectable_points: option(int),
    score_type: option(enum_score_types_enum),
    use_dropdown_for_points: option(bool),
  }
  and community_settings_on_conflict = {
    [@bs.as "constraint"]
    constraint_: enum_community_settings_constraint,
    update_columns: array(enum_community_settings_update_column),
    where: option(community_settings_bool_exp),
  }
  and community_settings_bool_exp = {
    _and: option(array(option(community_settings_bool_exp))),
    _not: option(community_settings_bool_exp),
    _or: option(array(option(community_settings_bool_exp))),
    allow_draws: option(boolean_comparison_exp),
    community: option(communities_bool_exp),
    community_id: option(int_comparison_exp),
    include_extra_time: option(boolean_comparison_exp),
    max_selectable_points: option(int_comparison_exp),
    score_type: option(score_types_enum_comparison_exp),
    use_dropdown_for_points: option(boolean_comparison_exp),
  }
  and boolean_comparison_exp = {
    _eq: option(bool),
    _gt: option(bool),
    _gte: option(bool),
    _in: option(array(bool)),
    _is_null: option(bool),
    _lt: option(bool),
    _lte: option(bool),
    _neq: option(bool),
    _nin: option(array(bool)),
  }
  and communities_bool_exp = {
    _and: option(array(option(communities_bool_exp))),
    _not: option(communities_bool_exp),
    _or: option(array(option(communities_bool_exp))),
    community_settings: option(community_settings_bool_exp),
    description: option(string_comparison_exp),
    id: option(int_comparison_exp),
    name: option(string_comparison_exp),
    players: option(players_bool_exp),
    results: option(results_bool_exp),
  }
  and string_comparison_exp = {
    _eq: option(string),
    _gt: option(string),
    _gte: option(string),
    _ilike: option(string),
    _in: option(array(string)),
    _is_null: option(bool),
    _like: option(string),
    _lt: option(string),
    _lte: option(string),
    _neq: option(string),
    _nilike: option(string),
    _nin: option(array(string)),
    _nlike: option(string),
    _nsimilar: option(string),
    _similar: option(string),
  }
  and int_comparison_exp = {
    _eq: option(int),
    _gt: option(int),
    _gte: option(int),
    _in: option(array(int)),
    _is_null: option(bool),
    _lt: option(int),
    _lte: option(int),
    _neq: option(int),
    _nin: option(array(int)),
  }
  and players_bool_exp = {
    _and: option(array(option(players_bool_exp))),
    _not: option(players_bool_exp),
    _or: option(array(option(players_bool_exp))),
    community: option(communities_bool_exp),
    communityId: option(int_comparison_exp),
    id: option(int_comparison_exp),
    name: option(string_comparison_exp),
    resultsAsPlayer1: option(results_bool_exp),
    resultsAsPlayer2: option(results_bool_exp),
  }
  and results_bool_exp = {
    _and: option(array(option(results_bool_exp))),
    _not: option(results_bool_exp),
    _or: option(array(option(results_bool_exp))),
    comment: option(string_comparison_exp),
    community: option(communities_bool_exp),
    communityId: option(int_comparison_exp),
    date: option(timestamptz_comparison_exp),
    extratime: option(boolean_comparison_exp),
    id: option(int_comparison_exp),
    player1: option(players_bool_exp),
    player1Id: option(int_comparison_exp),
    player1goals: option(int_comparison_exp),
    player2: option(players_bool_exp),
    player2Id: option(int_comparison_exp),
    player2goals: option(int_comparison_exp),
  }
  and timestamptz_comparison_exp = {
    _eq: option(DateTimeUtils.Datetime.t),
    _gt: option(DateTimeUtils.Datetime.t),
    _gte: option(DateTimeUtils.Datetime.t),
    _in: option(array(DateTimeUtils.Datetime.t)),
    _is_null: option(bool),
    _lt: option(DateTimeUtils.Datetime.t),
    _lte: option(DateTimeUtils.Datetime.t),
    _neq: option(DateTimeUtils.Datetime.t),
    _nin: option(array(DateTimeUtils.Datetime.t)),
  }
  and score_types_enum_comparison_exp = {
    _eq: option(enum_score_types_enum),
    _in: option(array(enum_score_types_enum)),
    _is_null: option(bool),
    _neq: option(enum_score_types_enum),
    _nin: option(array(enum_score_types_enum)),
  }
  and players_arr_rel_insert_input = {
    data: array(players_insert_input),
    on_conflict: option(players_on_conflict),
  }
  and players_insert_input = {
    community: option(communities_obj_rel_insert_input),
    communityId: option(int),
    id: option(int),
    name: option(string),
    resultsAsPlayer1: option(results_arr_rel_insert_input),
    resultsAsPlayer2: option(results_arr_rel_insert_input),
  }
  and results_arr_rel_insert_input = {
    data: array(results_insert_input),
    on_conflict: option(results_on_conflict),
  }
  and results_on_conflict = {
    [@bs.as "constraint"]
    constraint_: enum_results_constraint,
    update_columns: array(enum_results_update_column),
    where: option(results_bool_exp),
  }
  and players_on_conflict = {
    [@bs.as "constraint"]
    constraint_: enum_players_constraint,
    update_columns: array(enum_players_update_column),
    where: option(players_bool_exp),
  }
  and communities_on_conflict = {
    [@bs.as "constraint"]
    constraint_: enum_communities_constraint,
    update_columns: array(enum_communities_update_column),
    where: option(communities_bool_exp),
  }
  and players_obj_rel_insert_input = {
    data: players_insert_input,
    on_conflict: option(players_on_conflict),
  };

  type response = {insert_results_one: option(response_insert_results_one)};
  type rawResponse = response;
  type variables = {input: results_insert_input};
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"insert_results_one":{"n":""},"insert_results_one_date":{"c":"DateTimeUtils.Datetime"}}} |json}
  ];
  let wrapResponseConverterMap = {
    "DateTimeUtils.Datetime": DateTimeUtils.Datetime.serialize,
  };
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"insert_results_one":{"n":""},"insert_results_one_date":{"c":"DateTimeUtils.Datetime"}}} |json}
  ];
  let responseConverterMap = {
    "DateTimeUtils.Datetime": DateTimeUtils.Datetime.parse,
  };
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
    {json| {"__root":{"input":{"r":"results_insert_input"}},"Boolean_comparison_exp":{"_eq":{"n":""},"_gt":{"n":""},"_gte":{"n":""},"_in":{"n":""},"_is_null":{"n":""},"_lt":{"n":""},"_lte":{"n":""},"_neq":{"n":""},"_nin":{"n":""}},"Int_comparison_exp":{"_eq":{"n":""},"_gt":{"n":""},"_gte":{"n":""},"_in":{"n":""},"_is_null":{"n":""},"_lt":{"n":""},"_lte":{"n":""},"_neq":{"n":""},"_nin":{"n":""}},"String_comparison_exp":{"_eq":{"n":""},"_gt":{"n":""},"_gte":{"n":""},"_ilike":{"n":""},"_in":{"n":""},"_is_null":{"n":""},"_like":{"n":""},"_lt":{"n":""},"_lte":{"n":""},"_neq":{"n":""},"_nilike":{"n":""},"_nin":{"n":""},"_nlike":{"n":""},"_nsimilar":{"n":""},"_similar":{"n":""}},"communities_bool_exp":{"_and":{"n":"","na":"","r":"communities_bool_exp"},"_not":{"n":"","r":"communities_bool_exp"},"_or":{"n":"","na":"","r":"communities_bool_exp"},"community_settings":{"n":"","r":"community_settings_bool_exp"},"description":{"n":"","r":"String_comparison_exp"},"id":{"n":"","r":"Int_comparison_exp"},"name":{"n":"","r":"String_comparison_exp"},"players":{"n":"","r":"players_bool_exp"},"results":{"n":"","r":"results_bool_exp"}},"communities_insert_input":{"community_settings":{"n":"","r":"community_settings_arr_rel_insert_input"},"description":{"n":""},"id":{"n":""},"name":{"n":""},"players":{"n":"","r":"players_arr_rel_insert_input"},"results":{"n":"","r":"results_arr_rel_insert_input"}},"communities_obj_rel_insert_input":{"data":{"r":"communities_insert_input"},"on_conflict":{"n":"","r":"communities_on_conflict"}},"communities_on_conflict":{"where":{"n":"","r":"communities_bool_exp"}},"community_settings_arr_rel_insert_input":{"data":{"r":"community_settings_insert_input"},"on_conflict":{"n":"","r":"community_settings_on_conflict"}},"community_settings_bool_exp":{"_and":{"n":"","na":"","r":"community_settings_bool_exp"},"_not":{"n":"","r":"community_settings_bool_exp"},"_or":{"n":"","na":"","r":"community_settings_bool_exp"},"allow_draws":{"n":"","r":"Boolean_comparison_exp"},"community":{"n":"","r":"communities_bool_exp"},"community_id":{"n":"","r":"Int_comparison_exp"},"include_extra_time":{"n":"","r":"Boolean_comparison_exp"},"max_selectable_points":{"n":"","r":"Int_comparison_exp"},"score_type":{"n":"","r":"score_types_enum_comparison_exp"},"use_dropdown_for_points":{"n":"","r":"Boolean_comparison_exp"}},"community_settings_insert_input":{"allow_draws":{"n":""},"community":{"n":"","r":"communities_obj_rel_insert_input"},"community_id":{"n":""},"include_extra_time":{"n":""},"max_selectable_points":{"n":""},"score_type":{"n":""},"use_dropdown_for_points":{"n":""}},"community_settings_on_conflict":{"where":{"n":"","r":"community_settings_bool_exp"}},"players_arr_rel_insert_input":{"data":{"r":"players_insert_input"},"on_conflict":{"n":"","r":"players_on_conflict"}},"players_bool_exp":{"_and":{"n":"","na":"","r":"players_bool_exp"},"_not":{"n":"","r":"players_bool_exp"},"_or":{"n":"","na":"","r":"players_bool_exp"},"community":{"n":"","r":"communities_bool_exp"},"communityId":{"n":"","r":"Int_comparison_exp"},"id":{"n":"","r":"Int_comparison_exp"},"name":{"n":"","r":"String_comparison_exp"},"resultsAsPlayer1":{"n":"","r":"results_bool_exp"},"resultsAsPlayer2":{"n":"","r":"results_bool_exp"}},"players_insert_input":{"community":{"n":"","r":"communities_obj_rel_insert_input"},"communityId":{"n":""},"id":{"n":""},"name":{"n":""},"resultsAsPlayer1":{"n":"","r":"results_arr_rel_insert_input"},"resultsAsPlayer2":{"n":"","r":"results_arr_rel_insert_input"}},"players_obj_rel_insert_input":{"data":{"r":"players_insert_input"},"on_conflict":{"n":"","r":"players_on_conflict"}},"players_on_conflict":{"where":{"n":"","r":"players_bool_exp"}},"results_arr_rel_insert_input":{"data":{"r":"results_insert_input"},"on_conflict":{"n":"","r":"results_on_conflict"}},"results_bool_exp":{"_and":{"n":"","na":"","r":"results_bool_exp"},"_not":{"n":"","r":"results_bool_exp"},"_or":{"n":"","na":"","r":"results_bool_exp"},"comment":{"n":"","r":"String_comparison_exp"},"community":{"n":"","r":"communities_bool_exp"},"communityId":{"n":"","r":"Int_comparison_exp"},"date":{"n":"","r":"timestamptz_comparison_exp"},"extratime":{"n":"","r":"Boolean_comparison_exp"},"id":{"n":"","r":"Int_comparison_exp"},"player1":{"n":"","r":"players_bool_exp"},"player1Id":{"n":"","r":"Int_comparison_exp"},"player1goals":{"n":"","r":"Int_comparison_exp"},"player2":{"n":"","r":"players_bool_exp"},"player2Id":{"n":"","r":"Int_comparison_exp"},"player2goals":{"n":"","r":"Int_comparison_exp"}},"results_insert_input":{"comment":{"n":""},"community":{"n":"","r":"communities_obj_rel_insert_input"},"communityId":{"n":""},"date":{"n":"","c":"DateTimeUtils.Datetime"},"extratime":{"n":""},"id":{"n":""},"player1":{"n":"","r":"players_obj_rel_insert_input"},"player1Id":{"n":""},"player1goals":{"n":""},"player2":{"n":"","r":"players_obj_rel_insert_input"},"player2Id":{"n":""},"player2goals":{"n":""}},"results_on_conflict":{"where":{"n":"","r":"results_bool_exp"}},"score_types_enum_comparison_exp":{"_eq":{"n":""},"_in":{"n":""},"_is_null":{"n":""},"_neq":{"n":""},"_nin":{"n":""}},"timestamptz_comparison_exp":{"_eq":{"n":"","c":"DateTimeUtils.Datetime"},"_gt":{"n":"","c":"DateTimeUtils.Datetime"},"_gte":{"n":"","c":"DateTimeUtils.Datetime"},"_in":{"n":"","c":"DateTimeUtils.Datetime"},"_is_null":{"n":""},"_lt":{"n":"","c":"DateTimeUtils.Datetime"},"_lte":{"n":"","c":"DateTimeUtils.Datetime"},"_neq":{"n":"","c":"DateTimeUtils.Datetime"},"_nin":{"n":"","c":"DateTimeUtils.Datetime"}}} |json}
  ];
  let variablesConverterMap = {
    "DateTimeUtils.Datetime": DateTimeUtils.Datetime.serialize,
  };
  let convertVariables = v =>
    v
    ->ReasonRelay._convertObj(
        variablesConverter,
        variablesConverterMap,
        Js.undefined,
      );
};

module Utils = {
  external score_types_enum_toString: enum_score_types_enum => string =
    "%identity";
  external results_update_column_toString: enum_results_update_column => string =
    "%identity";
  external results_constraint_toString: enum_results_constraint => string =
    "%identity";
  external players_update_column_toString: enum_players_update_column => string =
    "%identity";
  external players_constraint_toString: enum_players_constraint => string =
    "%identity";
  external community_settings_update_column_toString:
    enum_community_settings_update_column => string =
    "%identity";
  external community_settings_constraint_toString:
    enum_community_settings_constraint => string =
    "%identity";
  external communities_update_column_toString:
    enum_communities_update_column => string =
    "%identity";
  external communities_constraint_toString:
    enum_communities_constraint => string =
    "%identity";
  open Types;
  let make_players_obj_rel_insert_input =
      (~data, ~on_conflict=?, ()): players_obj_rel_insert_input => {
    data,
    on_conflict,
  };

  let make_communities_on_conflict =
      (~constraint_, ~update_columns, ~where=?, ()): communities_on_conflict => {
    constraint_,
    update_columns,
    where,
  };

  let make_players_on_conflict =
      (~constraint_, ~update_columns, ~where=?, ()): players_on_conflict => {
    constraint_,
    update_columns,
    where,
  };

  let make_results_on_conflict =
      (~constraint_, ~update_columns, ~where=?, ()): results_on_conflict => {
    constraint_,
    update_columns,
    where,
  };

  let make_results_arr_rel_insert_input =
      (~data, ~on_conflict=?, ()): results_arr_rel_insert_input => {
    data,
    on_conflict,
  };

  let make_players_insert_input =
      (
        ~community=?,
        ~communityId=?,
        ~id=?,
        ~name=?,
        ~resultsAsPlayer1=?,
        ~resultsAsPlayer2=?,
        (),
      )
      : players_insert_input => {
    community,
    communityId,
    id,
    name,
    resultsAsPlayer1,
    resultsAsPlayer2,
  };

  let make_players_arr_rel_insert_input =
      (~data, ~on_conflict=?, ()): players_arr_rel_insert_input => {
    data,
    on_conflict,
  };

  let make_score_types_enum_comparison_exp =
      (~_eq=?, ~_in=?, ~_is_null=?, ~_neq=?, ~_nin=?, ())
      : score_types_enum_comparison_exp => {
    _eq,
    _in,
    _is_null,
    _neq,
    _nin,
  };

  let make_timestamptz_comparison_exp =
      (
        ~_eq=?,
        ~_gt=?,
        ~_gte=?,
        ~_in=?,
        ~_is_null=?,
        ~_lt=?,
        ~_lte=?,
        ~_neq=?,
        ~_nin=?,
        (),
      )
      : timestamptz_comparison_exp => {
    _eq,
    _gt,
    _gte,
    _in,
    _is_null,
    _lt,
    _lte,
    _neq,
    _nin,
  };

  let make_results_bool_exp =
      (
        ~_and=?,
        ~_not=?,
        ~_or=?,
        ~comment=?,
        ~community=?,
        ~communityId=?,
        ~date=?,
        ~extratime=?,
        ~id=?,
        ~player1=?,
        ~player1Id=?,
        ~player1goals=?,
        ~player2=?,
        ~player2Id=?,
        ~player2goals=?,
        (),
      )
      : results_bool_exp => {
    _and,
    _not,
    _or,
    comment,
    community,
    communityId,
    date,
    extratime,
    id,
    player1,
    player1Id,
    player1goals,
    player2,
    player2Id,
    player2goals,
  };

  let make_players_bool_exp =
      (
        ~_and=?,
        ~_not=?,
        ~_or=?,
        ~community=?,
        ~communityId=?,
        ~id=?,
        ~name=?,
        ~resultsAsPlayer1=?,
        ~resultsAsPlayer2=?,
        (),
      )
      : players_bool_exp => {
    _and,
    _not,
    _or,
    community,
    communityId,
    id,
    name,
    resultsAsPlayer1,
    resultsAsPlayer2,
  };

  let make_int_comparison_exp =
      (
        ~_eq=?,
        ~_gt=?,
        ~_gte=?,
        ~_in=?,
        ~_is_null=?,
        ~_lt=?,
        ~_lte=?,
        ~_neq=?,
        ~_nin=?,
        (),
      )
      : int_comparison_exp => {
    _eq,
    _gt,
    _gte,
    _in,
    _is_null,
    _lt,
    _lte,
    _neq,
    _nin,
  };

  let make_string_comparison_exp =
      (
        ~_eq=?,
        ~_gt=?,
        ~_gte=?,
        ~_ilike=?,
        ~_in=?,
        ~_is_null=?,
        ~_like=?,
        ~_lt=?,
        ~_lte=?,
        ~_neq=?,
        ~_nilike=?,
        ~_nin=?,
        ~_nlike=?,
        ~_nsimilar=?,
        ~_similar=?,
        (),
      )
      : string_comparison_exp => {
    _eq,
    _gt,
    _gte,
    _ilike,
    _in,
    _is_null,
    _like,
    _lt,
    _lte,
    _neq,
    _nilike,
    _nin,
    _nlike,
    _nsimilar,
    _similar,
  };

  let make_communities_bool_exp =
      (
        ~_and=?,
        ~_not=?,
        ~_or=?,
        ~community_settings=?,
        ~description=?,
        ~id=?,
        ~name=?,
        ~players=?,
        ~results=?,
        (),
      )
      : communities_bool_exp => {
    _and,
    _not,
    _or,
    community_settings,
    description,
    id,
    name,
    players,
    results,
  };

  let make_boolean_comparison_exp =
      (
        ~_eq=?,
        ~_gt=?,
        ~_gte=?,
        ~_in=?,
        ~_is_null=?,
        ~_lt=?,
        ~_lte=?,
        ~_neq=?,
        ~_nin=?,
        (),
      )
      : boolean_comparison_exp => {
    _eq,
    _gt,
    _gte,
    _in,
    _is_null,
    _lt,
    _lte,
    _neq,
    _nin,
  };

  let make_community_settings_bool_exp =
      (
        ~_and=?,
        ~_not=?,
        ~_or=?,
        ~allow_draws=?,
        ~community=?,
        ~community_id=?,
        ~include_extra_time=?,
        ~max_selectable_points=?,
        ~score_type=?,
        ~use_dropdown_for_points=?,
        (),
      )
      : community_settings_bool_exp => {
    _and,
    _not,
    _or,
    allow_draws,
    community,
    community_id,
    include_extra_time,
    max_selectable_points,
    score_type,
    use_dropdown_for_points,
  };

  let make_community_settings_on_conflict =
      (~constraint_, ~update_columns, ~where=?, ())
      : community_settings_on_conflict => {
    constraint_,
    update_columns,
    where,
  };

  let make_community_settings_insert_input =
      (
        ~allow_draws=?,
        ~community=?,
        ~community_id=?,
        ~include_extra_time=?,
        ~max_selectable_points=?,
        ~score_type=?,
        ~use_dropdown_for_points=?,
        (),
      )
      : community_settings_insert_input => {
    allow_draws,
    community,
    community_id,
    include_extra_time,
    max_selectable_points,
    score_type,
    use_dropdown_for_points,
  };

  let make_community_settings_arr_rel_insert_input =
      (~data, ~on_conflict=?, ()): community_settings_arr_rel_insert_input => {
    data,
    on_conflict,
  };

  let make_communities_insert_input =
      (
        ~community_settings=?,
        ~description=?,
        ~id=?,
        ~name=?,
        ~players=?,
        ~results=?,
        (),
      )
      : communities_insert_input => {
    community_settings,
    description,
    id,
    name,
    players,
    results,
  };

  let make_communities_obj_rel_insert_input =
      (~data, ~on_conflict=?, ()): communities_obj_rel_insert_input => {
    data,
    on_conflict,
  };

  let make_results_insert_input =
      (
        ~comment=?,
        ~community=?,
        ~communityId=?,
        ~date=?,
        ~extratime=?,
        ~id=?,
        ~player1=?,
        ~player1Id=?,
        ~player1goals=?,
        ~player2=?,
        ~player2Id=?,
        ~player2goals=?,
        (),
      )
      : results_insert_input => {
    comment,
    community,
    communityId,
    date,
    extratime,
    id,
    player1,
    player1Id,
    player1goals,
    player2,
    player2Id,
    player2goals,
  };

  let makeVariables = (~input): variables => {input: input};

  let make_response_insert_results_one_player2 =
      (~id, ~name): response_insert_results_one_player2 => {
    id,
    name,
  };

  let make_response_insert_results_one_player1 =
      (~id, ~name): response_insert_results_one_player1 => {
    id,
    name,
  };

  let make_response_insert_results_one =
      (
        ~player1,
        ~player2,
        ~player2goals,
        ~player1goals,
        ~extratime,
        ~date,
        ~id,
      )
      : response_insert_results_one => {
    player1,
    player2,
    player2goals,
    player1goals,
    extratime,
    date,
    id,
  };

  let makeOptimisticResponse = (~insert_results_one=?, ()): rawResponse => {
    insert_results_one: insert_results_one,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "input"
  }
],
v1 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v2 = [
  (v1/*: any*/),
  {
    "alias": null,
    "args": null,
    "kind": "ScalarField",
    "name": "name",
    "storageKey": null
  }
],
v3 = [
  {
    "alias": null,
    "args": [
      {
        "kind": "Variable",
        "name": "object",
        "variableName": "input"
      }
    ],
    "concreteType": "results",
    "kind": "LinkedField",
    "name": "insert_results_one",
    "plural": false,
    "selections": [
      {
        "alias": null,
        "args": null,
        "concreteType": "players",
        "kind": "LinkedField",
        "name": "player1",
        "plural": false,
        "selections": (v2/*: any*/),
        "storageKey": null
      },
      {
        "alias": null,
        "args": null,
        "concreteType": "players",
        "kind": "LinkedField",
        "name": "player2",
        "plural": false,
        "selections": (v2/*: any*/),
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
      (v1/*: any*/)
    ],
    "storageKey": null
  }
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "AddResultTableRowMutation",
    "selections": (v3/*: any*/),
    "type": "mutation_root",
    "abstractKey": null
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "AddResultTableRowMutation",
    "selections": (v3/*: any*/)
  },
  "params": {
    "cacheID": "fa1930dbe1caddfaef60ba9e5d26aa8b",
    "id": null,
    "metadata": {},
    "name": "AddResultTableRowMutation",
    "operationKind": "mutation",
    "text": "mutation AddResultTableRowMutation(\n  $input: results_insert_input!\n) {\n  insert_results_one(object: $input) {\n    player1 {\n      id\n      name\n    }\n    player2 {\n      id\n      name\n    }\n    player2goals\n    player1goals\n    extratime\n    date\n    id\n  }\n}\n"
  }
};
})() |json}
];
