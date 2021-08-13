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
  Move m(8, 24, DOUBLE_PAWN);
  Board b;
  b.makeMove(m);
  // EXPECT_EQ()
}