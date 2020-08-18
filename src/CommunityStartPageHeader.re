open Utils;
open Types;

[@react.component]
let make =
    (
      ~communityName: string,
      ~communitySettingsFragments,
      ~playerPickerFragment,
    ) => {
  let (addResultIsOpen, setAddResultIsOpen) = React.useState(_ => false);
  <>
    <MaterialUi.AppBar position=`Fixed color=`Secondary className="app-header">
      <MaterialUi.Toolbar>
        <>
          <div className="app-header-grouping">
            <HomeIcon className="app-header-item" />
            <MyPlayerHeaderLink communityName />
          </div>
          <div className="app-header-grow" />
          <MaterialUi.Fab
            onClick={_ => setAddResultIsOpen(oldIsOpen => !oldIsOpen)}
            color=`Secondary
            className="add-result-button">
            {addResultIsOpen ? <ArrowDropUp /> : <AddIcon />}
          </MaterialUi.Fab>
          <div className="add-result">
            <MaterialUi.ExpansionPanel expanded=addResultIsOpen>
              <span />
              <React.Suspense fallback={<MaterialUi.CircularProgress />}>
                <AddResult
                  communityName
                  communitySettingsFragments
                  playerPickerFragment
                  onResultAdded={_ => setAddResultIsOpen(_ => false)}
                />
              </React.Suspense>
            </MaterialUi.ExpansionPanel>
          </div>
          <RouteLink
            className="app-header-item" toPage={History(communityName)}>
            {text("History")}
          </RouteLink>
        </>
      </MaterialUi.Toolbar>
    </MaterialUi.AppBar>
    <MaterialUi.Toolbar />
  </>;
};
