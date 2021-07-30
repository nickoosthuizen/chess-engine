#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include <cstdint>

uint64_t nNorth(int n, uint64_t b);
uint64_t nSouth(int n, uint64_t b);
uint64_t nWest(int n, uint64_t b);
uint64_t nEast(int n, uint64_t b);
uint64_t nNorWest(int n, uint64_t b);
uint64_t nNorEast(int n, uint64_t b);
uint64_t nSoWest(int n, uint64_t b);
uint64_t nSoEast(int n, uint64_t b);

#endif