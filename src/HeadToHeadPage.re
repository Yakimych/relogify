[@react.component]
let make = (~communityName, ~player1Name, ~player2Name) =>
  <>
    <MaterialUiBox textAlign="center">
      <MaterialUiTypography variant="h5">
        {ReasonReact.string("Head to Head")}
      </MaterialUiTypography>
      <MaterialUiTypography variant="h4">
        {ReasonReact.string(player1Name ++ " vs " ++ player2Name)}
      </MaterialUiTypography>
    </MaterialUiBox>
  </>;
