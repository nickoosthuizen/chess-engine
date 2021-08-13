#include <gtest/gtest.h>
#include <vector>

#include "moveGen.h"
#include "constants.h"
#include "board.h"

TEST(shiftTests, northSouthOut) {
  EXPECT_EQ(oneSouth(0x0000000000000001), 0);
  EXPECT_EQ(oneSouth(0x00000000000000FF), 0);
  EXPECT_EQ(oneNorth(0xFF00000000000000), 0);
  EXPECT_EQ(oneNorth(0x8000000000000000), 0);
}

TEST(shiftTests, eastWestOut) {
  EXPECT_EQ(oneEast(0x0000010000000000), 0);
  EXPECT_EQ(oneEast(0x0000000000FF0000), 0x00000000007F0000);
  EXPECT_EQ(oneWest(0x0000800000000000), 0);
  EXPECT_EQ(oneWest(0x0000000000FF0000), 0x0000000000FE0000);
}

TEST(shiftTests, diagonalOut) {
  EXPECT_EQ(oneNoEast(0x0001000000000000), 0);
  EXPECT_EQ(oneNoWest(0x0080000000000000), 0);
  EXPECT_EQ(oneSoEast(0x0001000000000000), 0);
  EXPECT_EQ(oneSoWest(0x0080000000000000), 0);
}

TEST(shiftTests, genNorth) {
  EXPECT_EQ(oneNorth(0x0000000800000000), 0x0000080000000000);
  EXPECT_EQ(oneNorth(0x0000000000002900), 0x0000000000290000);
  EXPECT_EQ(oneNorth(0x00000000000000FF), 0x000000000000FF00);
}

TEST(shiftTests, genSouth) {
  EXPECT_EQ(oneSouth(0x0000080000000000), 0x0000000800000000);
  EXPECT_EQ(oneSouth(0x0000000000290000), 0x0000000000002900);
  EXPECT_EQ(oneSouth(0x000000000000FF00), 0x00000000000000FF);
}

TEST(shiftTests, genEast) {
  EXPECT_EQ(oneEast(0x20), 0x10);
  EXPECT_EQ(oneEast(0x98), 0x4C);
}

TEST(shiftTests, genWest) {
  EXPECT_EQ(oneWest(0x10), 0x20);
  EXPECT_EQ(oneWest(0x4C), 0x98);
}

TEST(shiftTests, genNoEast) {
  EXPECT_EQ(oneNoEast(0x008052), 0x402900);
}

TEST(shiftTests, genSoEast) {
  EXPECT_EQ(oneSoEast(0x008052), 0x000040);
}

TEST(shiftTests, genNoWest) {
  EXPECT_EQ(oneNoWest(0x008052), 0x00A400);
}

TEST(shiftTests, genSoWest) {
  EXPECT_EQ(oneSoWest(0x008052), 0x000000);
}

TEST(pawnTests, whitePawnPushOne) {
  EXPECT_EQ(whitePawnPush(0x0000FF, 0xFFFFFF), 0x00FF00);
  EXPECT_EQ(whitePawnPush(0x009000, 0xE0FFFF), 0x800000);
  EXPECT_EQ(whitePawnPush(0x000001, 0xFF00FF), 0x000000);
}

TEST(pawnTests, whitePawnPushTwo) {
  EXPECT_EQ(whitePawnPushTwo(0x000000000000FF00, 0x0000FFFFFFFF0000), 0x00000000FF000000);
  EXPECT_EQ(whitePawnPushTwo(0x000000000000FF00, 0x0000FFFFFF000000), 0x0000000000000000);
  EXPECT_EQ(whitePawnPushTwo(0x000000000000FF00, 0x0000FFFF00FF0000), 0x0000000000000000);
  EXPECT_EQ(whitePawnPushTwo(0x0000000000FF0000, 0xFFFFFFFFFFFFFFFF), 0x0000000000000000);
}

TEST(pawnTests, blackPawnPushOne) {
  EXPECT_EQ(blackPawnPush(0xFF0000, 0xFFFFFF), 0x00FF00);
  EXPECT_EQ(blackPawnPush(0x009000, 0xFFFFE0), 0x000080);
  EXPECT_EQ(blackPawnPush(0x010000, 0xFF00FF), 0x000000);
}

TEST(pawnTests, blackPawnPushTwo) {
  EXPECT_EQ(blackPawnPushTwo(0x00FF000000000000, 0x0000FFFFFFFF0000), 0x000000FF00000000);
  EXPECT_EQ(blackPawnPushTwo(0x00FF000000000000, 0x000000FFFFFF0000), 0x0000000000000000);
  EXPECT_EQ(blackPawnPushTwo(0x00FF000000000000, 0x0000FF00FFFF0000), 0x0000000000000000);
  EXPECT_EQ(blackPawnPushTwo(0x0000FF0000000000, 0xFFFFFFFFFFFFFFFF), 0x0000000000000000);
}

TEST(pawnTests, whitePawnAttack) {
  EXPECT_EQ(whitePawnAttack(0x00000001, 0x00000100), 0);
  EXPECT_EQ(whitePawnAttack(0x00000001, 0x00000200), 0x00000200);
  EXPECT_EQ(whitePawnAttack(0x00000001, 0x00000001), 0);
  EXPECT_EQ(whitePawnAttack(0x00000200, 0x00FF0000), 0x00050000);
  EXPECT_EQ(whitePawnAttack(0x00000200, 0x00FF00FF), 0x00050000);
  EXPECT_EQ(whitePawnAttack(0x00FF0000, 0xFF000000), 0xFF000000);
}

TEST(pawnTests, blackPawnAttack) {
  EXPECT_EQ(blackPawnAttack(0x01000000, 0x00010000), 0);
  EXPECT_EQ(blackPawnAttack(0x01000000, 0x00020000), 0x00020000);
  EXPECT_EQ(blackPawnAttack(0x01000000, 0x01000000), 0);
  EXPECT_EQ(blackPawnAttack(0x00020000, 0x0000FF00), 0x00000500);
  EXPECT_EQ(blackPawnAttack(0x00020000, 0xFF00FF00), 0x00000500);
  EXPECT_EQ(blackPawnAttack(0xFF000000, 0x00FF0000), 0x00FF0000);
}

TEST(knightTests, knightMove) {
  EXPECT_EQ(knightMove(WHITE_START & KNIGHT_START, ~(BLACK_START | WHITE_START), 0), 0x0000000000A50000);
  EXPECT_EQ(knightMove(BLACK_START & KNIGHT_START, ~(BLACK_START | WHITE_START), 0), 0x0000A50000000000);
  EXPECT_EQ(knightMove(0x0000100000, 0xFFFFFFFFFF, 0), 0x2844004428);
}

TEST(bishopTests, bishopMove) {
  EXPECT_EQ(bishopMove(WHITE_START & BISHOP_START, ~(BLACK_START | WHITE_START), BLACK_START), 0);
  EXPECT_EQ(bishopMove(BLACK_START & BISHOP_START, ~(BLACK_START | WHITE_START), WHITE_START), 0);
  EXPECT_EQ(bishopMove(0x0000000000420000, 0x00040818a500a510, 0), 0x00040818a500a510);
  EXPECT_EQ(bishopMove(0x0000000000420000, 0, 0x00040818a500a510), 0x00000000a500a500);
  EXPECT_EQ(bishopMove(0x0000000800000000, 0x0000FFFFFF000000, 0x0020000000200000), 0x0020140014200000);
}

TEST(rookTests, rookMove) {
  EXPECT_EQ(rookMove(WHITE_START & ROOK_START, ~(BLACK_START | WHITE_START), BLACK_START), 0);
  EXPECT_EQ(rookMove(BLACK_START & ROOK_START, ~(BLACK_START | WHITE_START), WHITE_START), 0);
  EXPECT_EQ(rookMove(0x0000000008000000, 0xFFFFFFFFFFFFFFFF, 0), 0x08080808f7080808);
  EXPECT_EQ(rookMove(0x0000000008000000, 0, 0xFFFFFFFFFFFFFFFF), 0x0000000814080000);
  EXPECT_EQ(rookMove(0x0000000042000000, 0x0000FFFFBDFF0000, 0xff02000000004000), 0x00024242bd424000);
}

/*
TEST(generateTests, genPawnBoards) {
  Board b, singlePush, doublePush, attackOne, attackTwo;
  std::vector<Board> nextBoards;
  b.clear();
  b.setColor(0x0000000000002000, white);
  b.setColor(0x0000000000500000, black);
  b.setPiece(0x0000000000502000, pawns);
  generatePawnBoards(nextBoards, b);
  singlePush.clear();
  singlePush.setColor(0x0000000000200000, white);
  singlePush.setColor(0x0000000000500000, black);
  singlePush.setPiece(0x0000000000700000, pawns);
  doublePush.clear();
  doublePush.setColor(0x0000000020000000, white);
  doublePush.setColor(0x0000000000500000, black);
  doublePush.setPiece(0x0000000020500000, pawns);
  doublePush.setPiece(0x0000000000200000, enPassat);
  attackOne.clear();
  attackOne.setColor(0x0000000000400000, white);
  attackOne.setColor(0x0000000000100000, black);
  attackOne.setPiece(0x0000000000500000, pawns);
  attackTwo.clear();
  attackTwo.setColor(0x0000000000100000, white);
  attackTwo.setColor(0x0000000000400000, black);
  attackTwo.setPiece(0x0000000000500000, pawns);
  std::vector<Board> expected = {singlePush, doublePush, attackTwo, attackOne};
  ASSERT_EQ(nextBoards.size(), expected.size());
  for (int i = 0; i < expected.size(); i++) {
    EXPECT_EQ(nextBoards[i], expected[i]) << "Difference at index " << i;
  }

}
*/