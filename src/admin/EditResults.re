open Utils;

module EditResultsFragment = [%relay.fragment
  {|
    fragment EditResultsFragment on resultsConnection {
      ...EditResultsTable_Results
      edges {
        node {
          id
        }
      }
    }
  |}
];

[@react.component]
let make =
    (
      ~communityName: string,
      ~editResultsFragment,
      ~playersFragment,
      ~communitySettingsFragment,
    ) => {
  let editResultsFragment = EditResultsFragment.use(editResultsFragment);
  let editResultsTableFragment = editResultsFragment.fragmentRefs;

  <>
    <Header page={AdminResultsPage(communityName)} />
    // TODO: Move this into ResultsTable?
    {editResultsFragment.edges->Belt.Array.length === 0
       ? <MaterialUi.Card className="no-result-info">
           <MaterialUi.CardContent>
             <MaterialUi.Typography variant=`H6>
               {text("No results reported during the selected time period")}
             </MaterialUi.Typography>
           </MaterialUi.CardContent>
         </MaterialUi.Card>
       : <EditResultsTable
           resultsFragment=editResultsTableFragment
           playersFragment
           communityName
           communitySettingsFragment
         />}
  </>;
};
