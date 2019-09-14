open Queries;

[@react.component]
let make = (~name: string) => {
  let communityCountByNameQuery =
    CommunityCountByNameQueryConfig.make(~name, ());
  let (communityCountByNameResult, _) =
    CommunityCountByNameQuery.use(
      ~variables=communityCountByNameQuery##variables,
      (),
    );

  <>
    {switch (communityCountByNameResult) {
     | Loading => <CircularProgress />
     | NoData
     | Error(_) => <span> {React.string("error")} </span>
     | Data(data) =>
       let isAvailable =
         switch (name) {
         | "new" => false
         | _ =>
           data##communities_aggregate##aggregate
           ->Belt.Option.mapWithDefault(false, a =>
               a##count->Belt.Option.mapWithDefault(false, c => c === 0)
             )
         };
       <>
         <div className="availability-indicator">
           <Zoom _in=isAvailable>
             <CheckCircle fontSize="large" htmlColor="green" />
           </Zoom>
         </div>
         <div className="availability-indicator">
           <Zoom _in={!isAvailable}>
             <NotAvailable fontSize="large" htmlColor="red" />
           </Zoom>
         </div>
       </>;
     }}
  </>;
};
