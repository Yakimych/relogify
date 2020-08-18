let adminPlayer1PointsCellStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~textAlign="right",
    ~paddingLeft="0",
    ~paddingRight="10px",
    (),
  );

let numberCellStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

let playerLinkStyle =
  ReactDOMRe.Style.make(
    ~textDecoration="none",
    ~color="rgba(0, 0, 0, 0.87)",
    (),
  );

let colonStyle =
  ReactDOMRe.Style.make(
    ~width="5px",
    ~paddingLeft="0",
    ~paddingRight="0",
    (),
  );

let headToHeadStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

let dateStyle = ReactDOMRe.Style.make(~width="100px", ());

let extraTimeStyle = ReactDOMRe.Style.make(~width="20px", ());

let getPlayerStyle = (isWinningPlayer: bool) =>
  ReactDOMRe.Style.make(~fontWeight=isWinningPlayer ? "bold" : "normal", ());
