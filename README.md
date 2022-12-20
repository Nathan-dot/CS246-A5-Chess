# CS246-A5-Chess
This is my CS246 Final Project, which involved developing a chess application with heavy emphasis on Object-Oriented Programming concepts and design/software architectural patterns.

## Summary
Per project requirements and some bonuses, this program has implemented the following:
- Player .vs. Player game mode 
- Robust Player .vs. Player interface
- Move History
- Undo Feature
- Setup Mode
- Text and Graphical Display via X11
Sample Example:
<div>
  <img alt="X11 Sample" src="chessboard.png"/>
</div>

## Command Interpreter:
- <i>game human human</i> starts a new game.
- <i>resign</i> concedes the game to your opponent
- Uppercase letters represent the white player's pieces while lowercase the black player's
- To move: <i>move src dst</i> (ex. <i>move e2 e4</i>)
- To undo: <i>undo</i> will undo each player's last move
- Castling is specified by two-square move for the king (for black: <i>move e1 g1</i>; for white: move e1 c1)
- Pawn promotion requires specification of the piece type to which the pawn is promoted: move e7 e8 Q.
- <i>setup</i> enters setup mode: this can only set up initial board configurations before the game is started
  - <i>\+ piece position</i> places the piece on the position (ex. <i>+ K e1</i>). This will replace a piece if one already exists on said square.
  - <i>\- position </i> removes the piece from the position (ex. <i>- e1</i>). This will do nothing if no piece exists on said square.
  - <i>= colour</i> will allow colour to move first
  - <i>done</i> leaves setup mode. This follows project requirements and will reject if the game is in an invalid state (i.e. Pawn is on a promotion square, There are not exactly two kings)
- <i>history</i> for viewing a move history of the game's past moves
  

## Documentation:
My Design Document is <a href="design.pdf">here</a>.
My UML diagram for this project is <a href="uml.pdf">here</a>.
