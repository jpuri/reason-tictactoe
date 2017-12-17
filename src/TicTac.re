type ticTacCell = CROSS | TICK | BLANK;

let str = ReasonReact.stringToElement;

/*
 * VALID MATCHES:
 * [(0,1,2), (3,4,5), (6,7,8), (0,3,6), (1,4,7), (2,5,8), (0,4,8), (2,4,6)];
 */
let checkMatch = (cells) => {
  ((cells[0] !== BLANK &&
    ((cells[0] === cells[1] && cells[1] === cells[2])
    || (cells[0] === cells[3] && cells[3] === cells[6])
    || (cells[0] === cells[4] && cells[4] === cells[8]))) ||
  (cells[1] !== BLANK &&
    ((cells[0] === cells[4] && cells[4] === cells[7]))) ||
  (cells[2] !== BLANK &&
    ((cells[2] === cells[5] && cells[5] === cells[8])
    || (cells[2] === cells[4] && cells[4] === cells[6]))) ||
  (cells[3] !== BLANK &&
    ((cells[3] === cells[4] && cells[4] === cells[5]))) ||
  (cells[6] !== BLANK &&
    ((cells[6] === cells[7] && cells[7] === cells[8]))))
};

module Cell = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~onClick, ~cellType, _) => {
    ...component,
    render: (_) => {
      <span onClick=(onClick) className="tictac-cell">
      (switch cellType {
        | TICK => <img src="./img/tick.svg"/>
        | CROSS => <img src="./img/cross.svg"/>
        | BLANK => str("")
      })
      </span>
    }
  };
};

type state = {
  gameOver: bool,
  currentActive: ticTacCell,
  cells: array(ticTacCell)
};

type action = SetCurrentActive(ticTacCell) | SetCell(int);

let component = ReasonReact.reducerComponent("TicTac");

let make = (_) => {
  ...component,
  initialState: () => {
    gameOver: false,
    currentActive: BLANK,
    cells: [|BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK|]
  },
  reducer: (action, {currentActive, cells} as state) => switch action {
    | SetCurrentActive(activeType) => {
      if (activeType === currentActive) {
        ReasonReact.Update({...state, currentActive: BLANK})
      } else {
        ReasonReact.Update({...state, currentActive: activeType})
      }
    }
    | SetCell(cellNumber) => {
      cells[cellNumber] = currentActive;
      ReasonReact.Update({currentActive: BLANK, cells, gameOver: checkMatch(cells)}) }
  },
  render: ({state: {currentActive, cells, gameOver}, reduce}) => {
    <div>
      <h1>(str("TIC TAC TOE"))</h1>
      <div className="tictac-row">
        <Cell onClick=(reduce((_evt) => SetCell(0))) cellType=(cells[0])/>
        <Cell onClick=(reduce((_evt) => SetCell(1))) cellType=(cells[1])/>
        <Cell onClick=(reduce((_evt) => SetCell(2))) cellType=(cells[2])/>
      </div>
      <div className="tictac-row">
        <Cell onClick=(reduce((_evt) => SetCell(3))) cellType=(cells[3])/>
        <Cell onClick=(reduce((_evt) => SetCell(4))) cellType=(cells[4])/>
        <Cell onClick=(reduce((_evt) => SetCell(5))) cellType=(cells[5])/>
      </div>
      <div className="tictac-row">
        <Cell onClick=(reduce((_evt) => SetCell(6))) cellType=(cells[6])/>
        <Cell onClick=(reduce((_evt) => SetCell(7))) cellType=(cells[7])/>
        <Cell onClick=(reduce((_evt) => SetCell(8))) cellType=(cells[8])/>
      </div>
      <div className="btn-section">
        (gameOver === false ?
          <span className="btn-top-section">
            <img
              className=(currentActive === TICK ? "btn btn-active" : "btn")
              onClick=(reduce((_evt) => SetCurrentActive(TICK)))
              src="./img/tick.svg"/>
            <img
              className=(currentActive === CROSS ? "btn btn-active" : "btn")
              onClick=(reduce((_evt) => SetCurrentActive(CROSS)))
              src="./img/cross.svg"/>
            <div>
              (str("First select TICK or CROSS then click some cell."))
            </div>
          </span>:
          <span>(str("GAME OVER"))</span>)
      </div>
    </div>
  }
};
