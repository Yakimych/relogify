open Utils;
open Queries;

[@react.component]
let make = (~communityName: string) => {
  let allResultsQuery = AllResultsQueryConfig.make(~communityName, ());

  let (resultsQuery, _) =
    AllResultsQuery.use(~variables=allResultsQuery##variables, ());

  <>
    <Link url={"/" ++ communityName}> {text("Start Page")} </Link>
    <div> {text("Elo rankings for " ++ communityName)} </div>
  </>;
};
