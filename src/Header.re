open Utils;
open Types;

[@react.component]
let make = (~page: page) => {
  <header className="app-header">
    {switch (page) {
     | Home => <div> {text("Result log")} </div>
     | CommunityStart(communityName) =>
       <>
         <div className="app-header-grouping">
           <HomeIcon />
           <MyPlayerHeaderLink communityName />
         </div>
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     | History(communityName) =>
       <>
         <div className="app-header-grouping">
           <RouteLink toPage={CommunityStart(communityName)}>
             <HomeIcon />
           </RouteLink>
           <MyPlayerHeaderLink communityName />
         </div>
         <span> {text("History")} </span>
       </>
     | PlayerHome(communityName, _) =>
       <>
         <RouteLink toPage={CommunityStart(communityName)}>
           <HomeIcon />
         </RouteLink>
         <div className="app-header-title"> {text("Player Results")} </div>
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     | HeadToHead(communityName, _, _) =>
       <>
         <div className="app-header-grouping">
           <RouteLink toPage={CommunityStart(communityName)}>
             <HomeIcon />
           </RouteLink>
           <MyPlayerHeaderLink communityName />
         </div>
         <div className="app-header-title"> {text("Head to Head")} </div>
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     }}
  </header>;
};
