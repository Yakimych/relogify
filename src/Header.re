open Utils;
open Types;

[@react.component]
let make = (~page: page) => {
  let (addResultIsOpen, setAddResultIsOpen) = React.useState(_ => false);
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
    <AppBar
      position="fixed"
      color={isAdmin ? "secondary" : "primary"}
      className="app-header">
      <Toolbar>
        {switch (page) {
         | Home => <div> {text("Relogify")} </div>
         | CreateCommunityPage => <div> {text("Create new community")} </div>
         | CommunityAdmin(communityName) =>
           <div> {text("Admin for " ++ communityName)} </div>
         | CommunityStart(communityName) =>
           <>
             <div className="app-header-grouping">
               <HomeIcon className="app-header-item" />
               <MyPlayerHeaderLink communityName />
             </div>
             <div className="app-header-grow" />
             <MaterialUi_Fab
               onClick={_ => setAddResultIsOpen(oldIsOpen => !oldIsOpen)}
               color=`Secondary
               className="add-result-button">
               {addResultIsOpen ? <ArrowDropUp /> : <AddIcon />}
             </MaterialUi_Fab>
             <div className="add-result">
               <ExpansionPanel expanded=addResultIsOpen>
                 <span />
                 <AddResult
                   communityName
                   onResultAdded={_ => setAddResultIsOpen(_ => false)}
                 />
               </ExpansionPanel>
             </div>
             <RouteLink
               className="app-header-item" toPage={History(communityName)}>
               {text("History")}
             </RouteLink>
           </>
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
      </Toolbar>
    </AppBar>
    <Toolbar />
  </>;
};
