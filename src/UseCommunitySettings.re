open Queries;
open ReasonApolloHooks.Query;

let useCommunitySettings = (communityName): variant(Types.communitySettings) => {
  let settingsQueryConfig =
    CommunitySettingsQueryConfig.make(~communityName, ());
  let (settingsQuery, _) =
    CommunitySettingsQuery.use(~variables=settingsQueryConfig##variables, ());

  switch (settingsQuery) {
  | Loading => Loading
  | NoData => NoData
  | Error(e) => Error(e)
  | Data(data) => Data(data |> toCommunitySettings)
  };
};
