open Jest;
open Expect;
open Utils;

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
