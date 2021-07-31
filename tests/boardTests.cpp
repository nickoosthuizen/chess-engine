#include <gtest/gtest.h>

#include "board.h"
#include "constants.h"

TEST(boardTests, initialization) {
  board b;
  EXPECT_EQ(b.getAllPieces(), WHITE_START | BLACK_START);
  EXPECT_EQ(b.getEmptySquares(), 0x0000FFFFFFFF0000);
  EXPECT_EQ(b.getBByType(white), WHITE_START);
  EXPECT_EQ(b.getBByType(black), BLACK_START);
  EXPECT_EQ(b.getBByType(rooks), ROOK_START);
  EXPECT_EQ(b.getBByType(kings), KING_START);
  EXPECT_EQ(b.getBByTypeAndColor(queens, white), QUEEN_START & WHITE_START);
  EXPECT_EQ(b.getBByTypeAndColor(kings, black), KING_START & BLACK_START);
}