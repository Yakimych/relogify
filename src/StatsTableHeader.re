open Utils;
open LeaderboardUtils;
open Styles;
open EloUtils;

module StatsTableHeaderFragment = [%relay.fragment
  {|
    fragment StatsTableHeader_ScoreType on community_settings {
      score_type
    }
  |}
];

[@react.component]
let make =
    (
      ~scoreTypeFragment,
      ~resultsWithRatings,
      ~onSortRequested,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
      ~sortBy,
      ~sortDirection,
    ) => {
  let scoreTypeFragment = StatsTableHeaderFragment.use(scoreTypeFragment);
  let texts = Texts.getScoreTypeTexts(scoreTypeFragment.score_type);

  let isWide = MaterialUi.Core.useMediaQueryString("(min-width: 600px)");
  let showEloRatings =
    dateFrom->Belt.Option.isNone && dateTo->Belt.Option.isNone;

  <MaterialUi.TableHead>
    <MaterialUi.TableRow>
      <MaterialUi.TableCell align=`Right>
        {text("Player")}
      </MaterialUi.TableCell>
      {showEloRatings && isWide
         ? <>
             <MaterialUi.Badge badgeContent={text("BETA")} color=`Primary>
               <MaterialUi.TableCell style=numberCellStyle>
                 <MaterialUi.Tooltip
                   title={text("Elo Rating")} placement=`Top>
                   <MaterialUi.TableSortLabel
                     active={
                       sortBy == EloRating(resultsWithRatings.ratingMap)
                     }
                     direction=sortDirection
                     onClick={_ =>
                       onSortRequested(
                         EloRating(resultsWithRatings.ratingMap),
                       )
                     }>
                     {text("Elo")}
                   </MaterialUi.TableSortLabel>
                 </MaterialUi.Tooltip>
               </MaterialUi.TableCell>
             </MaterialUi.Badge>
           </>
         : React.null}
      <MaterialUi.TableCell style=numberCellStyle>
        <MaterialUi.Tooltip placement=`Top title={text("Win Percentage")}>
          <MaterialUi.TableSortLabel
            active={sortBy === WinsPerMatch}
            direction=sortDirection
            onClick={_ => onSortRequested(WinsPerMatch)}>
            {text("W%")}
          </MaterialUi.TableSortLabel>
        </MaterialUi.Tooltip>
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=numberCellStyle>
        <MaterialUi.Tooltip placement=`Top title={text("Number of wins")}>
          <MaterialUi.TableSortLabel
            active={sortBy === MatchesWon}
            direction=sortDirection
            onClick={_ => onSortRequested(MatchesWon)}>
            {text("W")}
          </MaterialUi.TableSortLabel>
        </MaterialUi.Tooltip>
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=numberCellStyle>
        <MaterialUi.Tooltip placement=`Top title={text("Number of losses")}>
          <MaterialUi.TableSortLabel
            active={sortBy === MatchesLost}
            direction=sortDirection
            onClick={_ => onSortRequested(MatchesLost)}>
            {text("L")}
          </MaterialUi.TableSortLabel>
        </MaterialUi.Tooltip>
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=numberCellStyle>
        <MaterialUi.Tooltip placement=`Top title={text(texts.pointsWon)}>
          <MaterialUi.TableSortLabel
            active={sortBy === GoalsScored}
            direction=sortDirection
            onClick={_ => onSortRequested(GoalsScored)}>
            {text(texts.pointsWonShort)}
          </MaterialUi.TableSortLabel>
        </MaterialUi.Tooltip>
      </MaterialUi.TableCell>
      <MaterialUi.TableCell style=numberCellStyle>
        <MaterialUi.Tooltip placement=`Top title={text(texts.pointsLost)}>
          <MaterialUi.TableSortLabel
            active={sortBy === GoalsConceded}
            direction=sortDirection
            onClick={_ => onSortRequested(GoalsConceded)}>
            {text(texts.pointsLostShort)}
          </MaterialUi.TableSortLabel>
        </MaterialUi.Tooltip>
      </MaterialUi.TableCell>
      {isWide
         ? <>
             <MaterialUi.TableCell style=numberCellStyle>
               <MaterialUi.Tooltip
                 placement=`Top title={text(texts.pointDiff)}>
                 <MaterialUi.TableSortLabel
                   active={sortBy === GoalDiff}
                   direction=sortDirection
                   onClick={_ => onSortRequested(GoalDiff)}>
                   {text("+/-")}
                 </MaterialUi.TableSortLabel>
               </MaterialUi.Tooltip>
             </MaterialUi.TableCell>
             <MaterialUi.TableCell style=numberCellStyle>
               <MaterialUi.Tooltip
                 placement=`Top title={text(texts.pointsWonPerMatch)}>
                 <MaterialUi.TableSortLabel
                   active={sortBy === GoalsScoredPerMatch}
                   direction=sortDirection
                   onClick={_ => onSortRequested(GoalsScoredPerMatch)}>
                   {text(texts.pointsWonPerMatchShort)}
                 </MaterialUi.TableSortLabel>
               </MaterialUi.Tooltip>
             </MaterialUi.TableCell>
             <MaterialUi.TableCell style=numberCellStyle>
               <MaterialUi.Tooltip
                 placement=`Top title={text(texts.pointsLostPerMatch)}>
                 <MaterialUi.TableSortLabel
                   active={sortBy === GoalsConcededPerMatch}
                   direction=sortDirection
                   onClick={_ => onSortRequested(GoalsConcededPerMatch)}>
                   {text(texts.pointsLostPerMatchShort)}
                 </MaterialUi.TableSortLabel>
               </MaterialUi.Tooltip>
             </MaterialUi.TableCell>
           </>
         : React.null}
    </MaterialUi.TableRow>
  </MaterialUi.TableHead>;
};
