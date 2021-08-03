#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include <cstdint>
#include <vector>

#include "board.h"

uint64_t oneNorth(uint64_t b);
uint64_t oneSouth(uint64_t b);
uint64_t oneEast(uint64_t b);
uint64_t oneWest(uint64_t b);
uint64_t oneNoEast(uint64_t b);
uint64_t oneNoWest(uint64_t b);
uint64_t oneSoEast(uint64_t b);
uint64_t oneSoWest(uint64_t b);

void isolateBits(std::vector<uint64_t> &boards, uint64_t b);

uint64_t whitePawnPush(uint64_t whitePawns, uint64_t empty);
uint64_t whitePawnPushTwo(uint64_t whitePawns, uint64_t empty);
uint64_t blackPawnPush(uint64_t blackPawns, uint64_t empty);
uint64_t blackPawnPushTwo(uint64_t blackPawns, uint64_t empty);

uint64_t whitePawnAttack(uint64_t whitePawns, uint64_t blackPieces);
uint64_t blackPawnAttack(uint64_t blackPawns, uint64_t whitePieces);

void generatePawnBoards(std::vector<Board> &newBoards, Board current, int turn);

uint64_t knightMove(uint64_t knights, uint64_t empty, uint64_t pieces);

uint64_t bishopMove(uint64_t bishops, uint64_t empty, uint64_t pieces);

uint64_t rookMove(uint64_t rooks, uint64_t empty, uint64_t pieces);

uint64_t queenMove(uint64_t queen, uint64_t empty, uint64_t pieces);

uint64_t kingMove(uint64_t king, uint64_t empty, uint64_t pieces);

void generateMoves(std::vector<Board> &newBoards, Board current, int turn);

#endif