let numberCellStyle =
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    (),
  );

let hidableNumberCellStyle = pageWidth =>
  ReactDOMRe.Style.make(
    ~width="20px",
    ~paddingLeft="10px",
    ~paddingRight="0",
    ~display=Utils.cellDisplay(pageWidth),
    (),
  );

let playerLinkStyle =
  ReactDOMRe.Style.make(
    ~textDecoration="none",
    ~color="rgba(0, 0, 0, 0.87)",
    (),
  );
