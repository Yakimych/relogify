open Utils;
open Types;

[@react.component]
let make = (~page: page) => {
  let identity = ReactNetlifyIdentity.useIdentityContextSimple();
  let userEmail = identity.user->Belt.Option.mapWithDefault("", u => u.email);
  let isAdmin =
    identity.user
    ->Belt.Option.mapWithDefault(false, u =>
        u.appMetaData
        ->Belt.Option.flatMap(a => a.roles)
        ->Belt.Option.mapWithDefault(false, r =>
            r->Belt.Array.some(r => r === "Admin")
          )
      );

  <>
    <MaterialUi.AppBar
      position=`Fixed
      color={isAdmin ? `Secondary : `Primary}
      className="app-header">
      <MaterialUi.Toolbar>
        {switch (page) {
         | Home => <div> {text("Relogify")} </div>
         | CreateCommunityPage => <div> {text("Create new community")} </div>
         | CommunityAdmin(communityName) =>
           <div> {text("Admin for " ++ communityName)} </div>
         | CommunityStart(_) => React.null // TODO: Break up the header into smaller components (Extracted this one into CommunityStartPageHeader)
         | TopX(communityName) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
               <MyPlayerHeaderLink communityName />
             </div>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text("Top 5")} </div>
             <RouteLink
               className="app-header-item" toPage={History(communityName)}>
               {text("History")}
             </RouteLink>
           </>
         | History(communityName) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
               <MyPlayerHeaderLink communityName />
             </div>
             <div className="app-header-grow" />
             <div className="app-header-item"> {text("History")} </div>
           </>
         | PlayerHome(communityName, _) =>
           <>
             <RouteLink
               className="app-header-item"
               toPage={CommunityStart(communityName)}>
               <HomeIcon />
             </RouteLink>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text("Player Stats")} </div>
             <RouteLink
               className="app-header-item" toPage={History(communityName)}>
               {text("History")}
             </RouteLink>
           </>
         | HeadToHead(communityName, _, _) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
               <MyPlayerHeaderLink communityName />
             </div>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text("Head to Head")} </div>
             <RouteLink
               className="app-header-item" toPage={History(communityName)}>
               {text("History")}
             </RouteLink>
           </>
         | AdminSettingsPage(communityName) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
             </div>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text(userEmail)} </div>
             <div className="app-header-item"> {text("Settings")} </div>
             <RouteLink
               className="app-header-item"
               toPage={AdminPlayersPage(communityName)}>
               {text("Players")}
             </RouteLink>
             <RouteLink
               className="app-header-item"
               toPage={AdminResultsPage(communityName)}>
               {text("History")}
             </RouteLink>
           </>
         | AdminPlayersPage(communityName) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
             </div>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text(userEmail)} </div>
             <RouteLink
               className="app-header-item"
               toPage={AdminSettingsPage(communityName)}>
               {text("Settings")}
             </RouteLink>
             <div className="app-header-item"> {text("Players")} </div>
             <RouteLink
               className="app-header-item"
               toPage={AdminResultsPage(communityName)}>
               {text("History")}
             </RouteLink>
           </>
         | AdminResultsPage(communityName) =>
           <>
             <div className="app-header-grouping">
               <RouteLink
                 className="app-header-item"
                 toPage={CommunityStart(communityName)}>
                 <HomeIcon />
               </RouteLink>
             </div>
             <div className="app-header-grow" />
             <div className="app-header-title"> {text(userEmail)} </div>
             <RouteLink
               className="app-header-item"
               toPage={AdminSettingsPage(communityName)}>
               {text("Settings")}
             </RouteLink>
             <RouteLink
               className="app-header-item"
               toPage={AdminPlayersPage(communityName)}>
               {text("Players")}
             </RouteLink>
             <div className="app-header-item"> {text("History")} </div>
           </>
         }}
      </MaterialUi.Toolbar>
    </MaterialUi.AppBar>
    <MaterialUi.Toolbar />
  </>;
};
