open Utils;

module ExtraTimeColumnFragment = [%relay.fragment
  {|
    fragment ExtraTimeColumn_IncludeExtraTime on community_settings {
      include_extra_time
    }
  |}
];

[@react.component]
let make = (~extraTime: bool, ~includeExtraTimeFragment) => {
  let includeExtraTimeFragment =
    ExtraTimeColumnFragment.use(includeExtraTimeFragment);

  includeExtraTimeFragment.include_extra_time
    ? <MaterialUi.TableCell style=Styles.extraTimeStyle align=`Right>
        {text(extraTime ? "X" : "")}
      </MaterialUi.TableCell>
    : React.null;
};
