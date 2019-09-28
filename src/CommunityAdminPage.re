open Utils;

[@react.component]
let make = (~communityName) => {
  let identity = ReactNetlifyIdentity.useIdentityContextSimple();
  let handleClick = _ => identity.loginProvider(Google);

  // check if user is logged in
  let isLoggedIn = identity.isLoggedIn;

  <>
    // <Header page={CommunityAdmin(communityName)} />
    <div> {text("Admin for " ++ communityName)} </div>
    {isLoggedIn
       ? <>
           <span>
             {text(
                "Logged in as "
                ++ identity.user->Belt.Option.mapWithDefault("", u => u.email),
              )}
           </span>
           {identity.user
            ->Belt.Option.mapWithDefault(
                React.null,
                u => {
                  Js.log3("Identity: '", identity, "'");
                  u.role == "Admin"
                    ? <div> {text("Admin content")} </div>
                    : <span> {text("Access denied to admin content")} </span>;
                },
              )}
         </>
       : <button onClick=handleClick> {text("Login with Google")} </button>}
  </>;
};
