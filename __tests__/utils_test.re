open Jest;
open Expect;
open Utils;

describe("Utils", () =>
  describe("function", () => {
    test("should return true", () =>
      expect(true) |> toBe(true)
    );

    test("should return false", () =>
      expect(false) |> toBe(false)
    );
  })
);
