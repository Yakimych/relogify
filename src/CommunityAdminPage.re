open Utils;
open Types;

[@react.component]
let make = (~communityName, ~subRoute) => {
  let identity = ReactNetlifyIdentity.useIdentityContextSimple();
  let handleClick = _ => identity.loginProvider(Google);

  let isLoggedIn = identity.isLoggedIn;

  <>
    {isLoggedIn
       ? <>
           {identity.user
            ->Belt.Option.mapWithDefault(
                React.null,
                u => {
                  let isAdmin =
                    u.appMetaData
                    ->Belt.Option.flatMap(a => a.roles)
                    ->Belt.Option.mapWithDefault(false, r =>
                        r->Belt.Array.some(r => r === "Admin")
                      );

                  isAdmin
                    ? <div>
                        {text("Admin content")}
                        <RouteLink toPage={AdminSettingsPage(communityName)}>
                          {text("Settings")}
                        </RouteLink>
                        <RouteLink toPage={AdminResultsPage(communityName)}>
                          {text("Results")}
                        </RouteLink>
                        {switch (subRoute) {
                         | ["settings"] => <EditSettings communityName />
                         | ["results"]
                         | _ => <EditResults communityName />
                         }}
                      </div>
                    : <span> {text("Access denied to admin content")} </span>;
                },
              )}
         </>
       : <button onClick=handleClick> {text("Login with Google")} </button>}
  </>;
};
