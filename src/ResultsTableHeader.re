open Styles;
open Utils;

module ResultTableHeaderFragment = [%relay.fragment
  {|
    fragment ResultsTableHeader_CommunitySettings on community_settings {
      score_type
      include_extra_time
    }
  |}
];

[@react.component]
let make = (~communitySettingsFragment) => {
  let resultTableHeaderFragment =
    ResultTableHeaderFragment.use(communitySettingsFragment);
  let texts = Texts.getScoreTypeTexts(resultTableHeaderFragment.score_type);

  let isWide = MaterialUi.Core.useMediaQueryString("(min-width: 600px)");

  <MaterialUi.TableHead>
    <MaterialUi.TableRow>
      <MaterialUi.TableCell style=headToHeadStyle>
        {text("H2H")}
      </MaterialUi.TableCell>
      <MaterialUi.TableCell align=`Right>
        {text("Player1")}
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=numberCellStyle>
        {text(texts.pointsPlayerShort ++ "1")}
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=colonStyle />
      <MaterialUi.TableCell style=numberCellStyle>
        {text(texts.pointsPlayerShort ++ "2")}
      </MaterialUi.TableCell>
      <MaterialUi.TableCell> {text("Player2")} </MaterialUi.TableCell>
      {isWide && resultTableHeaderFragment.include_extra_time
         ? <MaterialUi.TableCell style=extraTimeStyle align=`Right>
             <MaterialUi.Tooltip title={text("Extra time")} placement=`Top>
               <span> {text("E")} </span>
             </MaterialUi.Tooltip>
           </MaterialUi.TableCell>
         : React.null}
      {isWide
         ? <MaterialUi.TableCell style=dateStyle>
             {text("Date")}
           </MaterialUi.TableCell>
         : React.null}
    </MaterialUi.TableRow>
  </MaterialUi.TableHead>;
};
