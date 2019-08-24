open Utils;

[%bs.raw {|require('./main.css')|}];

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div className="App">
    <header className="App-header"> {text("Result log")} </header>
    <>
      {switch (url.path->Belt.List.map(Js.Global.decodeURI)) {
       | [] => <Home />
       | [communityName] => <CommunityStartPage communityName />
       | [communityName, "history"] => <ResultHistory communityName />
       | [communityName, "elo"] => <EloRanking communityName />
       | [communityName, playerName] =>
         <PlayerResults communityName playerName />
       | [communityName, player1Name, player2Name] =>
         <HeadToHeadPage communityName player1Name player2Name />
       | _ => <div> {text("Invalid route")} </div>
       }}
    </>
  </div>;
};
