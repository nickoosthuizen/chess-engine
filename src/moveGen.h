#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include <cstdint>

uint64_t oneNorth(uint64_t b);
uint64_t oneSouth(uint64_t b);
uint64_t oneEast(uint64_t b);
uint64_t oneWest(uint64_t b);
uint64_t oneNoEast(uint64_t b);
uint64_t oneNoWest(uint64_t b);
uint64_t oneSoEast(uint64_t b);
uint64_t oneSoWest(uint64_t b);

uint64_t whitePawnPush(uint64_t whitePawns, uint64_t empty);
uint64_t whitePawnPushTwo(uint64_t whitePawns, uint64_t empty);
uint64_t blackPawnPush(uint64_t blackPawns, uint64_t empty);
uint64_t blackPawnPushTwo(uint64_t blackPawns, uint64_t empty);

uint64_t whitePawnAttack(uint64_t whitePawns, uint64_t blackPieces);
uint64_t blackPawnAttack(uint64_t blackPawns, uint64_t whitePieces);

// Both the move and attack for knights is the same
uint64_t knightMove(uint64_t knights, uint64_t emptyOrPieces);

uint64_t rookPush(uint64_t rooks, uint64_t empty);
uint64_t rookAttack(uint64_t rookPushBoard, uint64_t pieces);

uint64_t bishopPush(uint64_t bishops, uint64_t empty);
uint64_t bishopAttack(uint64_t bishopPushBoard, uint64_t pieces);

uint64_t queenPush(uint64_t queen, uint64_t empty);
uint64_t queenAttack(uint64_t queenPushBoard, uint64_t pieces);

uint64_t kingMove(uint64_t king, uint64_t emptyOrPieces);

#endif