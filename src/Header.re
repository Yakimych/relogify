open Utils;
open Types;

[@react.component]
let make = (~page: page) => {
  let (addingResult, setAddingResult) = React.useState(_ => false);

  <>
    <AppBar position="fixed" className="app-header">
      <Toolbar>
        {switch (page) {
         | Home => <div> {text("Result log")} </div>
         | CommunityStart(communityName) =>
           <>
             <div className="app-header-grouping">
               <HomeIcon className="app-header-item" />
               <MyPlayerHeaderLink communityName />
             </div>
             <div className="app-header-grow" />
             <button
               onClick={_ =>
                 setAddingResult(oldAddingResult => !oldAddingResult)
               }>
               <Fab color="secondary" className="add-result-button">
                 <AddIcon />
               </Fab>
             </button>
             <div className="add-result">
               <ExpansionPanel expanded=addingResult>
                 <span />
                 <AddResult
                   communityName
                   onResultAdded={_ => setAddingResult(_ => false)}
                 />
               </ExpansionPanel>
             </div>
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
         }}
      </Toolbar>
    </AppBar>
    <Toolbar />
  </>;
};
