open Jest;
open Expect;
open Utils;
open DateFns;

type withCurrentTimeTestCase = {
  mainDate: Js.Date.t,
  nowWithTime: Js.Date.t,
  expected: Js.Date.t,
};

Belt.List.forEach(
  [
    {
      mainDate: Js.Date.fromString("2019-01-01 12:35:05"),
      nowWithTime: Js.Date.fromString("2019-01-01 13:37:01"),
      expected: Js.Date.fromString("2019-01-01 13:37:01"),
    },
    {
      mainDate: Js.Date.fromString("2019-01-01 12:35:05"),
      nowWithTime: Js.Date.fromString("2019-05-05 13:37:01"),
      expected: Js.Date.fromString("2019-01-01 13:37:01"),
    },
    {
      mainDate: Js.Date.fromString("2019-01-01 12:35:05"),
      nowWithTime: Js.Date.fromString("2000-01-01 13:37:59"),
      expected: Js.Date.fromString("2019-01-01 13:37:59"),
    },
  ],
  testData =>
  describe("a suite", () =>
    test(
      formatDateTimeSeconds(testData.mainDate)
      ++ " withCurrentTime("
      ++ formatDateTimeSeconds(testData.nowWithTime)
      ++ ")"
      ++ " should return "
      ++ formatDateTimeSeconds(testData.expected),
      () =>
      expect(withCurrentTime(testData.mainDate, testData.nowWithTime))
      |> toEqual(testData.expected)
    )
  )
);

// TODO: Property-based test?
Belt.List.forEach(
  [
    Js.Date.fromString("2019-07-29"),
    Js.Date.fromString("2019-08-17"),
    Js.Date.fromString("2019-08-18"),
    Js.Date.fromString("2019-08-19"),
    Js.Date.fromString("2000-01-03"),
    Js.Date.fromString("1999-01-10"),
    Js.Date.fromString("2000-01-04"),
  ],
  date =>
  describe("a suite", () =>
    test(formatDate(date) ++ "|> startOfWeek() should return a Monday", () =>
      expect(startOfWeek(date, {"weekStartsOn": 1}) |> isMonday)
      |> toBe(true)
    )
  )
);
