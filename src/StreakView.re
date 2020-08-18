open Types;
open Utils;

[@react.component]
let make = (~streakName: string, ~streak: streak, ~playerName: string) =>
  <MaterialUi.Paper
    style={ReactDOMRe.Style.make(~marginTop="10px", ~marginBottom="6px", ())}>
    <MaterialUi.Typography>
      {text(streakName ++ ": ")}
      <span className="marked">
        {text(string_of_int(streak |> numberOfMatches) ++ " match(es)")}
      </span>
    </MaterialUi.Typography>
    <MaterialUi.Typography>
      {text("Started ")}
      <span className="date-time">
        {text(formatDateTime(streak |> startedAt))}
      </span>
    </MaterialUi.Typography>
    {streak
     ->endedAt
     ->Belt.Option.mapWithDefault(React.null, date =>
         <MaterialUi.Typography>
           {text("Ended ")}
           <span className="date-time"> {text(formatDateTime(date))} </span>
           {streak
            ->endedBy(playerName)
            ->Belt.Option.mapWithDefault(React.null, playerName =>
                <>
                  {text(" by ")}
                  <span className="marked"> {text(playerName)} </span>
                </>
              )}
         </MaterialUi.Typography>
       )}
  </MaterialUi.Paper>;
