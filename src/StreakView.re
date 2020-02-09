open Types;
open Utils;

[@react.component]
let make = (~streakName: string, ~streak: streak, ~playerName: string) =>
  <MaterialUi_Paper
    style={ReactDOMRe.Style.make(~marginTop="10px", ~marginBottom="6px", ())}>
    <MaterialUi_Typography>
      {text(streakName ++ ": ")}
      <span className="marked">
        {text(string_of_int(streak |> numberOfMatches) ++ " match(es)")}
      </span>
    </MaterialUi_Typography>
    <MaterialUi_Typography>
      {text("Started ")}
      <span className="date-time">
        {text(formatDateTime(streak |> startedAt))}
      </span>
    </MaterialUi_Typography>
    {streak
     ->endedAt
     ->Belt.Option.mapWithDefault(React.null, date =>
         <MaterialUi_Typography>
           {text("Ended ")}
           <span className="date-time"> {text(formatDateTime(date))} </span>
           {streak
            ->endedBy(playerName)
            ->Belt.Option.mapWithDefault(React.null, player =>
                <>
                  {text(" by ")}
                  <span className="marked"> {text(player.name)} </span>
                </>
              )}
         </MaterialUi_Typography>
       )}
  </MaterialUi_Paper>;
