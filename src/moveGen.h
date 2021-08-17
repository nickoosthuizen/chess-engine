#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include <cstdint>
#include <vector>
#include <functional>

#include "board.h"
#include "Move.h"
#include "constants.h"

// Precalulated knight move bitboards indexed by pos
const uint64_t knightLookupTable[64] = {
  0x20400, 0x50800, 0xa1100, 0x142200, 0x284400, 0x508800, 0xa01000, 0x402000, 
  0x2040004, 0x5080008, 0xa110011, 0x14220022, 0x28440044, 0x50880088, 0xa0100010, 0x40200020, 
  0x204000402, 0x508000805, 0xa1100110a, 0x1422002214, 0x2844004428, 0x5088008850, 0xa0100010a0, 0x4020002040, 
  0x20400040200, 0x50800080500, 0xa1100110a00, 0x142200221400, 0x284400442800, 0x508800885000, 0xa0100010a000, 0x402000204000, 
  0x2040004020000, 0x5080008050000, 0xa1100110a0000, 0x14220022140000, 0x28440044280000, 0x50880088500000, 0xa0100010a00000, 0x40200020400000, 
  0x204000402000000, 0x508000805000000, 0xa1100110a000000, 0x1422002214000000, 0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000, 0x4020002040000000, 
  0x400040200000000, 0x800080500000000, 0x1100110a00000000, 0x2200221400000000, 0x4400442800000000, 0x8800885000000000, 0x100010a000000000, 0x2000204000000000, 
  0x4020000000000, 0x8050000000000, 0x110a0000000000, 0x22140000000000, 0x44280000000000, 0x88500000000000, 0x10a00000000000, 0x20400000000000
}; 

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
uint64_t knightMove(uint64_t knights, uint64_t empty, uint64_t pieces);
uint64_t multKnightMove(uint64_t knights, uint64_t empty, uint64_t pieces);
uint64_t bishopMove(uint64_t bishops, uint64_t empty, uint64_t pieces);
uint64_t rookMove(uint64_t rooks, uint64_t empty, uint64_t pieces);
uint64_t queenMove(uint64_t queen, uint64_t empty, uint64_t pieces);
uint64_t kingMove(uint64_t king, uint64_t empty, uint64_t pieces);

bool areSquaresAttacked(const Board& b, color attacker, uint64_t attacked);
bool isInCheck(const Board& b, color side);

void generatePawnBoards(std::vector<Move>& newMoves, const Board& current);
// logic is the same for non pawn move boards
void generatePieceBoards(std::vector<Move>& newMoves, const Board& current, piece p, std::function<uint64_t(uint64_t, uint64_t, uint64_t)> pieceMove);
void generateCastleBoards(std::vector<Move>& newMoves, const Board& current);
void generateMoves(std::vector<Move>& newMoves, const Board& current);

#endif