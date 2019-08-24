open Utils;

[@react.component]
let make = (~communityName: string) => {
  Js.log("Elo");
  <> <div> {text("Elo rankings for " ++ communityName)} </div> </>;
};
