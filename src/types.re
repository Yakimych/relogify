type page =
  | Home
  | AdminSettingsPage(string)
  | AdminResultsPage(string)
  | CreateCommunityPage
  | CommunityStart(string)
  | CommunityAdmin(string)
  | History(string)
  | TopX(string)
  | PlayerHome(string, string)
  | HeadToHead(string, string, string);

type player = {
  id: int,
  name: string,
};

type result = {
  id: int,
  player1: player,
  player2: player,
  player1goals: int,
  player2goals: int,
  date: Js.Date.t,
  extratime: bool,
};

type playerStats = {
  playerName: string,
  matchesWon: int,
  matchesLost: int,
  goalsScored: int,
  goalsConceded: int,
};

type streak = {
  results: list(result),
  endingResult: option(result),
};

let numberOfMatches = (streak: streak) => streak.results->Belt.List.length;

let startedAt = (streak: streak) =>
  streak.results->Belt.List.reverse->Belt.List.headExn.date;

// TODO: Merge endedAt and endedBy and return a Tuple/type?
let endedAt = (streak: streak) =>
  streak.endingResult->Belt.Option.map(r => r.date);

let endedBy = (streak: streak, playerName: string) =>
  streak.endingResult
  ->Belt.Option.map(r =>
      r.player1.name === playerName ? r.player2 : r.player1
    );

type streaks = {
  longestStreak: option(streak),
  currentStreak: option(streak),
};

type scoreType = [ | `Goals | `Points];

let scoreTypeToString =
  fun
  | `Goals => "Goals"
  | `Points => "Points";

let toScoreType =
  fun
  | "Goals" => `Goals
  | "Points" => `Points
  | otherString => Js.Exn.raiseError("Unknown score type: " ++ otherString);

type communitySettings = {
  allowDraws: bool,
  maxSelectablePoints: int,
  scoreType,
  includeExtraTime: bool,
  useDropDownForPoints: bool,
};

let defaultCommunitySettings = {
  allowDraws: false,
  maxSelectablePoints: 9,
  scoreType: `Goals,
  includeExtraTime: true,
  useDropDownForPoints: true,
};

type editableResult = {
  id: int,
  player1Id: int,
  player2Id: int,
  player1Goals: int,
  player2Goals: int,
  extraTime: bool,
  date: Js.Date.t,
};

let toEditableResult = (result: result): editableResult => {
  id: result.id,
  player1Id: result.player1.id,
  player2Id: result.player2.id,
  player1Goals: result.player1goals,
  player2Goals: result.player2goals,
  extraTime: result.extratime,
  date: result.date,
};
