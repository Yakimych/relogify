open Utils;

[@react.component]
let make = (~communityName, ~subRoute) => {
  let identity = ReactNetlifyIdentity.useIdentityContextSimple();
  let handleClick = _ => identity.loginProvider(Google);

  let isLoggedIn = identity.isLoggedIn;
  let isLoggedInAsAdmin =
    identity.user
    ->Belt.Option.flatMap(u => u.appMetaData)
    ->Belt.Option.flatMap(a => a.roles)
    ->Belt.Option.mapWithDefault(false, r =>
        r->Belt.Array.some(r => r === "Admin")
      );

  Js.log2("isLoggedIn: ", isLoggedIn);
  Js.log2("isLoggedInAsAdmin: ", isLoggedInAsAdmin);

  switch (isLoggedIn, isLoggedInAsAdmin) {
  | (true, true) => <CommunityAdminPage communityName subRoute />
  | (true, false) => <span> {text("Access denied to admin content")} </span>
  | (false, _) =>
    <MaterialUi.Button
      color=`Primary
      variant=`Outlined
      onClick=handleClick
      style={ReactDOMRe.Style.make(~margin="20px", ())}>
      {text("Login with Google")}
    </MaterialUi.Button>
  };
};
