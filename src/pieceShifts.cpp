#include <cstdint>

#include "pieceShifts.h"
#include "constants.h"

/*
 * Ex: 000001000000 (hypothetical 12 bit unsigned integer)
 *    0000
 *    0100
 *    0000
 * 
 *    One north = 010000000000
 *    0100
 *    0000
 *    0000
 * 
 *    One East = 000000100000
 *    0000
 *    0010
 *    0000
 */

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

uint64_t knightMove(uint64_t n) {
  uint64_t knightMoves = 0;
  uint64_t temp = 0;
  temp = oneNoWest(n);
  knightMoves |= oneWest(temp) | oneNorth(temp);
  temp = oneNoEast(n);
  knightMoves |= oneEast(temp) | oneNorth(temp);
  temp = oneSoWest(n);
  knightMoves |= oneWest(temp) | oneSouth(temp);
  temp = oneSoEast(n);
  knightMoves |= oneEast(temp) | oneSouth(temp);
  return knightMoves;
}

uint64_t bishopMove(uint64_t b) {
  return ray(b, oneNoWest) | ray(b, oneNoEast) | ray(b, oneSoWest) | ray(b, oneSoEast);
}

uint64_t rookMove(uint64_t r) {
  return ray(r, oneNorth) | ray(r, oneSouth) | ray(r, oneWest) | ray(r, oneEast); 
}

uint64_t queenMove(uint64_t q) {
  return bishopMove(q) | rookMove(q);
}

uint64_t kingMove(uint64_t k) {
  return (oneNoWest(k) | oneNorth(k) | oneNoEast(k) | oneEast(k) |
          oneSoEast(k) | oneSouth(k) | oneSoWest(k) | oneWest(k));
}

uint64_t ray(uint64_t b, std::function<uint64_t(uint64_t)> shift) {
  uint64_t temp = shift(b);
  uint64_t ray = 0;
  while (temp) {
    ray |= temp;
    temp = shift(temp);
  }
  return ray;
}