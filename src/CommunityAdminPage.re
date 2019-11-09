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

  <>
    {isLoggedIn
       ? isLoggedInAsAdmin
           ? {
             switch (subRoute) {
             | ["settings"] => <EditSettings communityName />
             | ["results"]
             | _ => <EditResults communityName />
             };
           }
           : <span> {text("Access denied to admin content")} </span>
       : <Button
           color="primary"
           variant="outlined"
           onClick=handleClick
           style={ReactDOMRe.Style.make(~margin="20px", ())}>
           {text("Login with Google")}
         </Button>}
  </>;
};
