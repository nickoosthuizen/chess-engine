#ifndef PIECE_SHIFTS_H
#define PIECE_SHIFTS_H

#include <cstdint>
#include <functional>

#include "constants.h"

// shifts bits in specified direction,
inline uint64_t oneNorth(uint64_t b) { return b << 8; }
inline uint64_t oneSouth(uint64_t b) { return b >> 8; }
inline uint64_t oneEast(uint64_t b) { return (b & NOT_FILE_H) >> 1; }
inline uint64_t oneWest(uint64_t b) { return (b & NOT_FILE_A) << 1; }
inline uint64_t oneNoEast(uint64_t b) { return (b & NOT_FILE_H) << 7; }
inline uint64_t oneNoWest(uint64_t b) { return (b & NOT_FILE_A) << 9; }
inline uint64_t oneSoEast(uint64_t b) { return (b & NOT_FILE_H) >> 9; }
inline uint64_t oneSoWest(uint64_t b) { return (b & NOT_FILE_A) >> 7; }

inline uint64_t getLSB(uint64_t b) { return b & -b; }

// pawn logic is different for each side and for pushes and attacks
// generate the full pawn push bit board
uint64_t whitePawnPush(uint64_t whitePawns, uint64_t empty);
uint64_t whitePawnPushTwo(uint64_t whitePawns, uint64_t empty);
uint64_t blackPawnPush(uint64_t blackPawns, uint64_t empty);
uint64_t blackPawnPushTwo(uint64_t blackPawns, uint64_t empty);

// generate the full pawn attack bit board
uint64_t whitePawnAttack(uint64_t whitePawns, uint64_t blackPieces);
uint64_t blackPawnAttack(uint64_t blackPawns, uint64_t whitePieces);

// generate the full piece move and attack bit board
uint64_t knightMove(uint64_t n);
uint64_t bishopMove(uint64_t b);
uint64_t rookMove(uint64_t r);
uint64_t queenMove(uint64_t q);
uint64_t kingMove(uint64_t k);

uint64_t ray(uint64_t b, std::function<uint64_t(uint64_t)> shift);

#endif