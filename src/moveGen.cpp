#include "moveGen.h"
#include "constants.h"

uint64_t oneNorth(uint64_t b) { return b << 8; }
uint64_t oneSouth(uint64_t b) { return b >> 8; }
uint64_t oneEast(uint64_t b) { return (b & NOT_H_FILE) >> 1; }
uint64_t oneWest(uint64_t b) { return (b & NOT_A_FILE) << 1; }
uint64_t oneNoEast(uint64_t b) { return (b & NOT_H_FILE) << 7; }
uint64_t oneNoWest(uint64_t b) { return (b & NOT_A_FILE) << 9; }
uint64_t oneSoEast(uint64_t b) { return (b & NOT_H_FILE) >> 9; }
uint64_t oneSoWest(uint64_t b) { return (b & NOT_A_FILE) >> 7; }