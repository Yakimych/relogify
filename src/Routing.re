open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div className="App">
    <header className="App-header"> {text("Result log")} </header>
    <>
      {switch (url.path) {
       | [] => <Home />
       | [communityName] =>
         <CommunityStartPage
           communityName={Js.Global.decodeURI(communityName)}
         />
       | [communityName, "history"] =>
         <ResultHistory communityName={Js.Global.decodeURI(communityName)} />
       | [communityName, playerName] =>
         <PlayerResults
           communityName={Js.Global.decodeURI(communityName)}
           playerName={Js.Global.decodeURI(playerName)}
         />
       | [communityName, player1Name, player2Name] =>
         <HeadToHeadPage
           communityName={Js.Global.decodeURI(communityName)}
           player1Name={Js.Global.decodeURI(player1Name)}
           player2Name={Js.Global.decodeURI(player2Name)}
         />
       | _ => <div> {text("Invalid route")} </div>
       }}
    </>
  </div>;
};
