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
                  let isAdmin =
                    u.appMetaData
                    ->Belt.Option.mapWithDefault(false, a =>
                        a.roles
                        ->Belt.Option.mapWithDefault(false, r =>
                            r->Belt.Array.some(r => r === "Admin")
                          )
                      );

                  isAdmin
                    ? <div>
                        {text("Admin content")}
                        <EditResults communityName />
                      </div>
                    : <span> {text("Access denied to admin content")} </span>;
                },
              )}
         </>
       : <button onClick=handleClick> {text("Login with Google")} </button>}
  </>;
};
