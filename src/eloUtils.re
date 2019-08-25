open Types;

let initialRanking = 1200;
let initialRankings: Belt_MapString.t(int) = Belt_MapString.empty;

let getEloRankings = (results: list(result)): Belt_MapString.t(int) => Belt_MapString.empty;
