open Styles;
open Utils;
open Types;
open EloUtils;
open UseCommunitySettings;
open PlayerStatsUtils;

let getPlayerStyle = (isWinningPlayer: bool) =>
  ReactDOMRe.Style.make(~fontWeight=isWinningPlayer ? "bold" : "normal", ());

let headToHeadStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

let colonStyle =
  ReactDOMRe.Style.make(
    ~width="5px",
    ~paddingLeft="0",
    ~paddingRight="0",
    (),
  );

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

let extraTimeStyle = ReactDOMRe.Style.make(~width="20px", ());

let getHighlightedClassName =
    (newResults: option(list(int)), currentResult: matchResult) => {
  let resultIsFresh =
    newResults
    ->Belt.Option.map(n => n->Belt.List.some(id => id == currentResult.id))
    ->Belt.Option.getWithDefault(false);

  resultIsFresh ? "highlighted" : "";
};

let getWinningLosingRowClassName = (mainPlayerWon: bool) =>
  mainPlayerWon ? "winning-row" : "";

[@react.component]
let make =
    (
      ~results: list(resultWithRatings),
      // This can be removed as soon as ratings are persisted. Ratings will always be shown then.
      ~temp_showRatings: bool=false,
      ~resultIdsToHighlight: option(list(int))=?,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
    ) => {
  let settingsQuery = useCommunitySettings(communityName);

  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  let isWide = MaterialUi.useMediaQuery("(min-width: 600px)");

  switch (settingsQuery) {
  | Loading => <MaterialUi_CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
    let texts = Texts.getScoreTypeTexts(communitySettings.scoreType);

    <MaterialUi_Paper>
      <div className="title">
        <MaterialUi_Typography variant=`H6>
          {text("Results")}
        </MaterialUi_Typography>
      </div>
      <MaterialUi_Table size=`Small>
        <MaterialUi_TableHead>
          <MaterialUi_TableRow>
            <MaterialUi_TableCell style=headToHeadStyle>
              {text("H2H")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell align=`Right>
              {text("Player1")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell style=numberCellStyle>
              {text(texts.pointsPlayerShort ++ "1")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell style=colonStyle />
            <MaterialUi_TableCell style=numberCellStyle>
              {text(texts.pointsPlayerShort ++ "2")}
            </MaterialUi_TableCell>
            <MaterialUi_TableCell> {text("Player2")} </MaterialUi_TableCell>
            {isWide && communitySettings.includeExtraTime
               ? <MaterialUi_TableCell style=extraTimeStyle align=`Right>
                   <MaterialUi_Tooltip
                     title={text("Extra time")} placement=`Top>
                     <span> {text("E")} </span>
                   </MaterialUi_Tooltip>
                 </MaterialUi_TableCell>
               : React.null}
            {isWide
               ? <MaterialUi_TableCell style=dateStyle>
                   {text("Date")}
                 </MaterialUi_TableCell>
               : React.null}
          </MaterialUi_TableRow>
        </MaterialUi_TableHead>
        <MaterialUi_TableBody>
          {results
           ->Belt.List.map(resultWithRatings => {
               let result = resultWithRatings.result;
               let player1Won = hasPlayer1Won(result);
               let player2Won = hasPlayer2Won(result);
               let mainPlayerWon = hasMainPlayerWon(mainPlayerName, result);
               let formattedDate = formatDate(result.date);

               <MaterialUi_TableRow
                 key={string_of_int(result.id)}
                 className={
                   getHighlightedClassName(resultIdsToHighlight, result)
                   ++ " "
                   ++ getWinningLosingRowClassName(mainPlayerWon)
                 }>
                 <MaterialUi_TableCell style=headToHeadStyle>
                   <RouteLink
                     toPage={
                       HeadToHead(
                         communityName,
                         result.player1.name,
                         result.player2.name,
                       )
                     }>
                     {text("H2H")}
                   </RouteLink>
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell
                   style={getPlayerStyle(player1Won)} align=`Right>
                   <RouteLink
                     toPage={PlayerHome(communityName, result.player1.name)}
                     style=playerLinkStyle>
                     {text(result.player1.name)}
                   </RouteLink>
                   {temp_showRatings && isWide
                      ? <Rating
                          onClick={_ =>
                            showGraphForPlayer(result.player1.name)
                          }
                          ratingBefore={resultWithRatings.player1RatingBefore}
                          ratingAfter={resultWithRatings.player1RatingAfter}
                        />
                      : React.null}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell style=numberCellStyle>
                   {text(string_of_int(result.player1goals))}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell style=colonStyle>
                   {text(":")}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell style=numberCellStyle>
                   {text(string_of_int(result.player2goals))}
                 </MaterialUi_TableCell>
                 <MaterialUi_TableCell style={getPlayerStyle(player2Won)}>
                   <RouteLink
                     toPage={PlayerHome(communityName, result.player2.name)}
                     style=playerLinkStyle>
                     {text(result.player2.name)}
                   </RouteLink>
                   {temp_showRatings && isWide
                      ? <Rating
                          onClick={_ =>
                            showGraphForPlayer(result.player2.name)
                          }
                          ratingBefore={resultWithRatings.player2RatingBefore}
                          ratingAfter={resultWithRatings.player2RatingAfter}
                        />
                      : React.null}
                 </MaterialUi_TableCell>
                 {isWide && communitySettings.includeExtraTime
                    ? <MaterialUi_TableCell style=extraTimeStyle align=`Right>
                        {text(result.extratime ? "X" : "")}
                      </MaterialUi_TableCell>
                    : React.null}
                 {isWide
                    ? <MaterialUi_TableCell>
                        {text(formattedDate)}
                      </MaterialUi_TableCell>
                    : React.null}
               </MaterialUi_TableRow>;
             })
           ->Array.of_list
           ->React.array}
        </MaterialUi_TableBody>
      </MaterialUi_Table>
      {graphIsShownForPlayer->Belt.Option.mapWithDefault(
         React.null, playerName =>
         <EloGraphDialog
           isOpen=true
           onClose=hideGraphForPlayer
           playerName
           resultsWithRatings=results
         />
       )}
    </MaterialUi_Paper>;
  };
};
