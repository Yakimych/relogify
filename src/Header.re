open Utils;
open Types;

[@react.component]
let make = (~page: page) =>
  <header className="App-header">
    {switch (page) {
     | Home => <div> {text("Result log")} </div>
     | CommunityStart(communityName) =>
       <>
         <HomeIcon />
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     | History(communityName) =>
       <>
         <RouteLink toPage={CommunityStart(communityName)}>
           <HomeIcon />
         </RouteLink>
         <span> {text("History")} </span>
       </>
     | PlayerHome(communityName, _) =>
       <>
         <RouteLink toPage={CommunityStart(communityName)}>
           <HomeIcon />
         </RouteLink>
         <div className="App-header-title"> {text("Player Results")} </div>
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     | HeadToHead(communityName, _, _) =>
       <>
         <RouteLink toPage={CommunityStart(communityName)}>
           <HomeIcon />
         </RouteLink>
         <div className="App-header-title"> {text("Head to Head")} </div>
         <RouteLink toPage={History(communityName)}>
           {text("History")}
         </RouteLink>
       </>
     }}
  </header>;
