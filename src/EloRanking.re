open Utils;
open EloUtils;
open Queries;

[@react.component]
let make = (~communityName: string) => {
  let allResultsQuery = AllResultsQueryConfig.make(~communityName, ());

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  <>
    <Link url={"/" ++ communityName}> {text("Start Page")} </Link>
    <div> {text("Elo rankings for " ++ communityName)} </div>
    <div>
      {switch (resultsQuery) {
       | Loading => <CircularProgress />
       | NoData
       | Error(_) => <span> {text("Error")} </span>
       | Data(data) =>
         let eloRatings = getEloRankings(data##results |> toRecord);

         <ul>
           {eloRatings->Belt.List.map(((playerName, rating)) =>
              <li>
                {text(
                   playerName
                   ++ ": "
                   ++ Js.Float.toString(Js.Math.round(rating)),
                 )}
              </li>
            )
            |> Array.of_list
            |> ReasonReact.array}
         </ul>;
       }}
    </div>
  </>;
};
