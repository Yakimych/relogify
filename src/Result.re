open Styles;
open Utils;
open EloUtils;

module ResultFragment = [%relay.fragment
  {|
    fragment Result_SingleResult on results {
      player1 {
        id
        name
      }
      player2 {
        id
        name
      }
      player2goals
      player1goals
      extratime
      date
      id
    }
  |}
];

// TODO: Implement highlighting
let getHighlightedClassName =
    (newResults: option(list(string)), currentResult) => {
  "";
};

let getWinningLosingRowClassName = (mainPlayerWon: bool) =>
  mainPlayerWon ? "winning-row" : "";

let hasPlayer1Won = (result: Result_SingleResult_graphql.Types.fragment) =>
  PlayerStatsUtils.isWin(result.player1goals, result.player2goals);

let hasPlayer2Won = (result: Result_SingleResult_graphql.Types.fragment) =>
  PlayerStatsUtils.isWin(result.player2goals, result.player1goals);

let hasMainPlayerWon = (mainPlayerName: option(string), result) => {
  let player1Won = hasPlayer1Won(result);
  let player2Won = hasPlayer2Won(result);
  let mainPlayerWon =
    player1Won
    && mainPlayerName === Some(result.player1.name)
    || player2Won
    && mainPlayerName === Some(result.player2.name);

  mainPlayerWon;
};

[@react.component]
let make =
    (
      ~result,
      ~resultWithRatings: resultWithRatings,
      ~communityName: string,
      ~mainPlayerName: option(string),
      ~temp_showRatings,
      ~includeExtraTimeFragment,
      ~showGraphForPlayer,
    ) => {
  let result = ResultFragment.use(result);
  // let lastFetchedResultsRef = React.useRef(Js.Nullable.null);
  //  let result = resultWithRatings.result;
  let player1Won = hasPlayer1Won(result);
  let player2Won = hasPlayer2Won(result);
  let mainPlayerWon = hasMainPlayerWon(mainPlayerName, result);
  let formattedDate = formatDate(result.date);

  let resultIdsToHighlight = None;

  let isWide = MaterialUi.Core.useMediaQueryString("(min-width: 600px)");

  <MaterialUi.TableRow
    key={result.id}
    className={
      getHighlightedClassName(resultIdsToHighlight, result)
      ++ " "
      ++ getWinningLosingRowClassName(mainPlayerWon)
    }>
    <MaterialUi.TableCell style=headToHeadStyle>
      <RouteLink
        toPage={
          HeadToHead(communityName, result.player1.name, result.player2.name)
        }>
        {text("H2H")}
      </RouteLink>
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style={getPlayerStyle(player1Won)} align=`Right>
      <RouteLink
        toPage={PlayerHome(communityName, result.player1.name)}
        style=playerLinkStyle>
        {text(result.player1.name)}
      </RouteLink>
      {temp_showRatings && isWide
         ? <Rating
             onClick={_ => showGraphForPlayer(result.player1.name)}
             ratingBefore={resultWithRatings.player1RatingBefore}
             ratingAfter={resultWithRatings.player1RatingAfter}
           />
         : React.null}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      {text(string_of_int(result.player1goals))}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=colonStyle>
      {text(":")}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style=numberCellStyle>
      {text(string_of_int(result.player2goals))}
    </MaterialUi.TableCell>
    <MaterialUi.TableCell style={getPlayerStyle(player2Won)}>
      <RouteLink
        toPage={PlayerHome(communityName, result.player2.name)}
        style=playerLinkStyle>
        {text(result.player2.name)}
      </RouteLink>
      {temp_showRatings && isWide
         ? <Rating
             onClick={_ => showGraphForPlayer(result.player2.name)}
             ratingBefore={resultWithRatings.player2RatingBefore}
             ratingAfter={resultWithRatings.player2RatingAfter}
           />
         : React.null}
    </MaterialUi.TableCell>
    {isWide
       ? <ExtraTimeColumn
           extraTime={result.extratime}
           includeExtraTimeFragment
         />
       : React.null}
    {isWide
       ? <MaterialUi.TableCell> {text(formattedDate)} </MaterialUi.TableCell>
       : React.null}
  </MaterialUi.TableRow>;
};
