#include "board.h"
#include "moveGen.h"

#include <iostream>

int main() {
  Board b, singlePush, doublePush, attackOne, attackTwo;
  std::vector<Board> nextBoards;
  b.clear();
  b.setColor(0x0000000000002000, white);
  b.setColor(0x0000000000500000, black);
  b.setPiece(0x0000000000502000, pawns);
  generatePawnBoards(nextBoards, b, white);
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
}