# Chess Engine
Chess engine built using a bitboard based approach

## About

The engine is capable of enumerating valid moves from a given chess position,
making move suggestions from a given chess position, and playing a CLI
game of chess.

## Installation

### Dependencies

This project uses Cmake for convenenient compilation:

https://cmake.org/

### Compiling

It is recommended to add a build folder to the project after pulling to avoid polluting 
the source. This folder can have any name, such as 'build'.

After pulling the repository:

`mkdir build

`cd  build

`cmake ..

`cmake --build .

The engine executable will now be in the src directory and the test executable in
test.

## Usage

### Starting

The chess-engine program takes no command line arguments and is simply ran 
with:

`./chess-engine

### Using

When the program is first started, the board will be in the starting position.

The engine supports the following commands:

`display

Print the current state of the board to the screen.

`fen FEN_STRING

Update the board to the position described by FEN_STRING. FEN_STRING is 
a string in Forsyth-Edwards Notation (not enclosed in quotes). 

Example (Starting Board): rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

`move MOVE

Make a move on the current board. MOVE is formatted as a character and a digit
representing the file and rank of the piece to move, and a character and a digit
representing the file and rank of the square to move the piece to. If move is a pawn
promotion, a character representing the piece to promote the pawn to is included.

Promotions: n: knight, b: bishop, r: rook, q: queen

Example: h3h5 - Moves a piece from file h rank 3 to file h rank 5

Promotion Example: a2a1q - Moves a pawn from file a rank 1 to file a rank 1 and promotes it to a queen

`perft DEPTH

Output the number of legal boards at depth DEPTH that can be generated from the 
current position.

`divide DEPTH

Enumerate the legal moves from the current board and Output the perft of each
at DEPTH - 1.

`suggest

Ask the chess engine to select a move to suggest at the current board.

`play

Start playing a game against the engine. The user starts first as white.
The board is displayed at each move and the user is prompted to choose 
a move in the move format specified above. The engine makes its own moves in response.

## Resources on Chess Programming

### Chess Programming in General

https://www.chessprogramming.org/Main_Page

### Forsyth Edwards Notation

https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation

https://www.chessprogramming.org/Forsyth-Edwards_Notation


