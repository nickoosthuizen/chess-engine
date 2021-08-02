#include "moveGen.h"
#include "constants.h"

uint64_t oneNorth(uint64_t b) { return b << 8; }
uint64_t oneSouth(uint64_t b) { return b >> 8; }
uint64_t oneEast(uint64_t b) { return (b & NOT_FILE_H) >> 1; }
uint64_t oneWest(uint64_t b) { return (b & NOT_FILE_A) << 1; }
uint64_t oneNoEast(uint64_t b) { return (b & NOT_FILE_H) << 7; }
uint64_t oneNoWest(uint64_t b) { return (b & NOT_FILE_A) << 9; }
uint64_t oneSoEast(uint64_t b) { return (b & NOT_FILE_H) >> 9; }
uint64_t oneSoWest(uint64_t b) { return (b & NOT_FILE_A) >> 7; }

uint64_t whitePawnPush(uint64_t whitePawns, uint64_t empty) {
  return oneNorth(whitePawns) & empty;
}

uint64_t whitePawnPushTwo(uint64_t whitePawns, uint64_t empty) {
  uint64_t firstPush = oneNorth(whitePawns & RANK_2) & empty;
  return oneNorth(firstPush) & empty;
}

uint64_t blackPawnPush(uint64_t blackPawns, uint64_t empty) {
  return oneSouth(blackPawns) & empty;
}

uint64_t blackPawnPushTwo(uint64_t blackPawns, uint64_t empty) {
  uint64_t firstPush = oneSouth(blackPawns & RANK_7) & empty;
  return oneSouth(firstPush) & empty;
}

uint64_t whitePawnAttack(uint64_t whitePawns, uint64_t blackPieces) {
  return (oneNoWest(whitePawns) | oneNoEast(whitePawns)) & blackPieces;
}

uint64_t blackPawnAttack(uint64_t blackPawns, uint64_t whitePieces) {
  return (oneSoWest(blackPawns) | oneSoEast(blackPawns)) & whitePieces;
}

uint64_t knightMove(uint64_t knights, uint64_t empty, uint64_t pieces) {
  uint64_t newKnights = 0;
  uint64_t temp = 0;
  temp = oneNoWest(knights);
  newKnights = newKnights | oneWest(temp) | oneNorth(temp);
  temp = oneNoEast(knights);
  newKnights = newKnights | oneEast(temp) | oneNorth(temp);
  temp = oneSoWest(knights);
  newKnights = newKnights | oneWest(temp) | oneSouth(temp);
  temp = oneSoEast(knights);
  newKnights = (newKnights | oneEast(temp) | oneSouth(temp)) & (empty | pieces);
  return newKnights;
}

uint64_t bishopMove(uint64_t bishops, uint64_t empty, uint64_t pieces) {
  uint64_t bishopMoveBoard = 0;
  uint64_t temp = bishops;
  while (temp) {
    temp = oneNoWest(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while (temp) {
    temp = oneNoEast(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while (temp) {
    temp = oneSoWest(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while(temp) {
    temp = oneSoEast(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  return bishopMoveBoard;
}

uint64_t rookMove(uint64_t rooks, uint64_t empty, uint64_t pieces) {
  uint64_t rookMoveBoard = 0;
  uint64_t temp = rooks;
  while (temp) {
    temp = oneNorth(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneSouth(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneWest(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneEast(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  return rookMoveBoard;
}

uint64_t queenMove(uint64_t queen, uint64_t empty, uint64_t pieces) {
  return bishopMove(queen, empty, pieces) | rookMove(queen, empty, pieces);
}

uint64_t kingMove(uint64_t king, uint64_t empty, uint64_t pieces) {
  return oneNoWest(king) | oneNorth(king) | oneNoEast(king) | oneEast(king) |
          oneSoEast(king) | oneSouth(king) | oneSoWest(king) | oneWest(king) & 
           (empty | pieces);
}