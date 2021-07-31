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

#endif