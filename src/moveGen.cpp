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