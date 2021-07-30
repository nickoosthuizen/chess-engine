#include "moveGen.h"

uint64_t nNorth(int n, uint64_t b) { return b << (n * 8); }
uint64_t nSouth(int n, uint64_t b) { return b >> (n * 8); }
uint64_t nWest(int n, uint64_t b) { return b << n; }
uint64_t nEast(int n, uint64_t b) { return b >> n; }
uint64_t nNorWest(int n, uint64_t b) { return b << (n * 9); }
uint64_t nNorEast(int n, uint64_t b) { return b << (n * 7); }
uint64_t nSoWest(int n, uint64_t b) { return b >> (n * 7); }
uint64_t nSoEast(int n, uint64_t b) { return b >> (n * 9); }