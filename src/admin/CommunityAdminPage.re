// TODO: Top query here!

[@react.component]
let make = (~communityName, ~subRoute) => {
  switch (subRoute) {
  | ["settings"] => <EditSettings communityName />
  | ["players"] => <EditPlayers communityName />
  | ["results"]
  | _ => <EditResults communityName />
  };
};
