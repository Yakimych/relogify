open Queries;
open ApolloHooks;

let useCommunitySettings =
    (communityName): Query.variant(Types.communitySettings) => {
  let (settingsQuery, _) =
    useQuery(
      ~variables=CommunitySettingsQuery.makeVariables(~communityName, ()),
      CommunitySettingsQuery.definition,
    );

  switch (settingsQuery) {
  | Loading => Loading
  | NoData => NoData
  | Error(e) => Error(e)
  | Data(data) => Data(data |> toCommunitySettings)
  };
};
