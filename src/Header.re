open Utils;

type page =
  | Home
  | CommunityStart(string)
  | History(string)
  | PlayerHome(string, string)
  | HeadToHead(string, string, string);

[@react.component]
let make = (~page: page) =>
  <header className="App-header">
    <Link url="/"> <HomeIcon /> </Link>
    {switch (page) {
     | Home => <div> {text("Result log")} </div>
     | CommunityStart(communityName) =>
       <>
         <span> {text("Start: " ++ communityName)} </span>
         <Link url={"/" ++ communityName ++ "/history"}>
           {text("History")}
         </Link>
       </>
     | History(communityName) =>
       <>
         <Link url={"/" ++ communityName}> {text("Start")} </Link>
         <span> {text("History for " ++ communityName)} </span>
       </>
     | PlayerHome(communityName, playerName) =>
       <>
         <Link url={"/" ++ communityName}> {text("Start")} </Link>
         <Link url={"/" ++ communityName ++ "/history"}>
           {text("History")}
         </Link>
         <div> {text(communityName ++ " / Stats for " ++ playerName)} </div>
       </>
     | HeadToHead(communityName, player1Name, player2Name) =>
       <>
         <Link url={"/" ++ communityName}> {text("Start")} </Link>
         <Link url={"/" ++ communityName ++ "/history"}>
           {text("History")}
         </Link>
         <div>
           {text(
              communityName
              ++ " / Head to Head between "
              ++ player1Name
              ++ " and "
              ++ player2Name,
            )}
         </div>
       </>
     }}
  </header>;
