open Styles;
open Utils;
open Types;
open EloUtils;
open UseCommunitySettings;

module Query = [%relay.query
  {|
    query ResultsTableQuery(
      $communityName: String!
      $dateFrom: timestamptz
      $dateTo: timestamptz
    ) {
      results_connection(
        where: {
          community: { name: { _eq: $communityName } }
          date: { _gte: $dateFrom, _lte: $dateTo }
        }
        order_by: { date: desc }
      ) {
        edges {
          node {
            ...Result_SingleResult
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
        }
      }
      community_settings_connection(
        where: { community: { name: { _eq: $communityName } } }
      ) {
        edges {
          node {
            ...ExtraTimeColumn_IncludeExtraTime
          }
        }
      }
    }
  |}
];

let getHighlightedClassName =
    (newResults: option(list(string)), currentResult: matchResult) => {
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
      // TODO: Implement highlighting
      ~resultIdsToHighlight: option(list(string))=?,
      ~communityName: string,
      ~mainPlayerName: option(string)=?,
      ~dateFrom: option(Js.Date.t)=?,
      ~dateTo: option(Js.Date.t)=?,
    ) => {
  // TODO: Remove the query from the parent or more the query higher up and pass the fragments down instead?
  let localResultsQueryData =
    Query.use(
      ~variables={
        communityName,
        dateFrom: dateFrom->Belt.Option.map(Js.Date.toISOString),
        dateTo: dateTo->Belt.Option.map(Js.Date.toISOString),
      },
      (),
    );

  let includeExtraTimeFragment =
    localResultsQueryData.community_settings_connection.edges
    ->Belt.Array.getExn(0).
      node.
      fragmentRefs;

  let settingsQuery = useCommunitySettings(communityName);

  let (graphIsShownForPlayer, setGraphIsShownForPlayer) =
    React.useState(_ => None);

  let showGraphForPlayer = (playerName: string) =>
    setGraphIsShownForPlayer(_ => Some(playerName));

  let hideGraphForPlayer = () => setGraphIsShownForPlayer(_ => None);

  let isWide = MaterialUi.Core.useMediaQueryString("(min-width: 600px)");

  switch (settingsQuery) {
  | Loading => <MaterialUi.CircularProgress />
  | NoData
  | Error(_) => <span> {text("Error")} </span>
  | Data(communitySettings) =>
    let texts = Texts.getScoreTypeTexts(communitySettings.scoreType);

    <MaterialUi.Paper>
      <div className="title">
        <MaterialUi.Typography variant=`H6>
          {text("Results")}
        </MaterialUi.Typography>
      </div>
      <MaterialUi.Table size=`Small>
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
            {isWide && communitySettings.includeExtraTime
               ? <MaterialUi.TableCell style=extraTimeStyle align=`Right>
                   <MaterialUi.Tooltip
                     title={text("Extra time")} placement=`Top>
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
        </MaterialUi.TableHead>
        <MaterialUi.TableBody>
          {localResultsQueryData.results_connection.edges
           ->Belt.Array.map(localResult => {
               let resultWithRatings: resultWithRatings =
                 results |> List.find(r => r.result.id === localResult.node.id);

               <Result
                 temp_showRatings
                 result={localResult.node.fragmentRefs}
                 resultWithRatings
                 communityName
                 mainPlayerName
                 includeExtraTimeFragment
                 showGraphForPlayer
               />;
             })
           ->React.array}
        </MaterialUi.TableBody>
      </MaterialUi.Table>
      {graphIsShownForPlayer->Belt.Option.mapWithDefault(
         React.null, playerName =>
         <EloGraphDialog
           isOpen=true
           onClose=hideGraphForPlayer
           playerName
           resultsWithRatings=results
         />
       )}
    </MaterialUi.Paper>;
  };
};
