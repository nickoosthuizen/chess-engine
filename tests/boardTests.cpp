#include <gtest/gtest.h>
#include <string>

#include "board.h"
#include "constants.h"
#include "Move.h"

TEST(boardTests, defaultConstructor) {
  Board b;
  EXPECT_EQ(b.getAllPieces(), WHITE_START | BLACK_START);
  EXPECT_EQ(b.getEmptySquares(), 0x0000FFFFFFFF0000);
  EXPECT_EQ(b.getBByColor(white), WHITE_START);
  EXPECT_EQ(b.getBByColor(black), BLACK_START);
  EXPECT_EQ(b.getBByPiece(rooks), ROOK_START);
  EXPECT_EQ(b.getBByPiece(kings), KING_START);
  EXPECT_EQ(b.getBByPieceAndColor(queens, white), QUEEN_START & WHITE_START);
  EXPECT_EQ(b.getBByPieceAndColor(kings, black), KING_START & BLACK_START);
}

TEST(boardTests, fenConstructor) {
  std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board defaultConstructor;
  Board fenConstructor(fen);
  EXPECT_EQ(defaultConstructor, fenConstructor);
}

TEST(boardTests, makeMove) {
  Board b;
  b.makeMove(Move(8, 24, DOUBLE_PAWN));
  std::string fen = "rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1";
  EXPECT_EQ(Board(fen), b);
  b.makeMove(Move(62, 47, REGULAR));
  fen = "r1bqkbnr/pppppppp/n7/8/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 1 2";
  EXPECT_EQ(Board(fen), b);
}

TEST(boardTests, unMakeMove) {
  Board b;
  b.makeMove(Move(8, 24, DOUBLE_PAWN));
  b.unMakeMove();
  EXPECT_EQ(b, Board());
  b.makeMove(Move(8, 24, DOUBLE_PAWN));
  b.makeMove(Move(62, 47, REGULAR));
  b.unMakeMove();
  std::string fen = "rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1";
  EXPECT_EQ(b, Board(fen));
}