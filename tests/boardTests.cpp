#include <gtest/gtest.h>

#include "board.h"
#include "constants.h"

TEST(boardTests, initialization) {
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