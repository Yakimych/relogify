open Utils;

[@react.component]
let make =
    (
      ~communityName,
      ~resultsFragment,
      ~playersFragment,
      ~communitySettingsFragment,
    ) => {
  // TODO: Remove? Make fragments that require start/end dates parametrizable?
  let (startDate, endDate) = getCurrentWeek();
  <>
    <CommunityStartPageHeader
      communityName
      communitySettingsFragment
      playerPickerFragment=playersFragment
    />
    <Stats
      statsResultsFragment=resultsFragment
      scoreTypeFragment=communitySettingsFragment
      communityName
      dateFrom=startDate
      dateTo=endDate
    />
    <ResultsTable
      resultsTableFragment=resultsFragment
      communitySettingsFragment
      communityName
      dateFrom=startDate
      dateTo=endDate
      // highlightNewResults=true
    />
  </>;
};
