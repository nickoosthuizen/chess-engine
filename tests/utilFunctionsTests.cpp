#include <gtest/gtest.h>

#include "utilFunctions.h"

TEST(utilFunctionTests, bitToSquare) {
  EXPECT_EQ(bitToSquare(0x0100000000000000), "h8");
  EXPECT_EQ(bitToSquare(0x0400000000000000), "f8");
  EXPECT_EQ(bitToSquare(0x0000800000000000), "a6");
  EXPECT_EQ(bitToSquare(0x0000000000000008), "e1");
}

/*
TEST(utilFunctionTests, posToBitBoard) {
  EXPECT_EQ(posToBitBoard(0), 0x0000000000000080);
  EXPECT_EQ(posToBitBoard(8), 0x0000000000008000);
  EXPECT_EQ(posToBitBoard(7), 0x0000000000000001);
  EXPECT_EQ(posToBitBoard(63), 0x0100000000000000);
  EXPECT_EQ(posToBitBoard(45), 0x0000030000000000);
}
*/

TEST(utilFunctionTests, bitBoardToPos) {
  EXPECT_EQ(bitBoardToPos(0x0000000000000080), 7);
  EXPECT_EQ(bitBoardToPos(0x0000000000000001), 0);
  EXPECT_EQ(bitBoardToPos(0x0100000000000000), 56);
  EXPECT_EQ(bitBoardToPos(0x8000000000000000), 63);
  EXPECT_EQ(bitBoardToPos(0x0000000000000400), 10);
}

TEST(utilFunctionTests, posToBBtoPos) {
  EXPECT_EQ(bitBoardToPos(posToBitBoard(7)), 7);
  EXPECT_EQ(bitBoardToPos(posToBitBoard(0)), 0);
  EXPECT_EQ(bitBoardToPos(posToBitBoard(35)), 35);
  EXPECT_EQ(bitBoardToPos(posToBitBoard(63)), 63);
}

TEST(utilFunctionTests, BBtoPostoBB) {
  EXPECT_EQ(posToBitBoard(bitBoardToPos(0x0000040000000000)), 0x0000040000000000);
  EXPECT_EQ(posToBitBoard(bitBoardToPos(0x8000000000000000)), 0x8000000000000000);
  EXPECT_EQ(posToBitBoard(bitBoardToPos(0x0000000000000001)), 0x0000000000000001);
}

TEST(utilFunctionTests, squareToBit) {
  EXPECT_EQ(squareToBit("h1"), 0x0000000000000001);
  EXPECT_EQ(squareToBit("h3"), 0x0000000000010000);
  EXPECT_EQ(squareToBit("a1"), 0x0000000000000080);
  EXPECT_EQ(squareToBit("a8"), 0x8000000000000000);
  EXPECT_EQ(squareToBit("d5"), 0x0000001000000000);
}
