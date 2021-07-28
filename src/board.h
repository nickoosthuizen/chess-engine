#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

struct board {
  uint64_t occupied;
  uint64_t empty;
  uint64_t pieces[2];
  uint64_t pawns[2];
  uint64_t knights[2];
  uint64_t bishops[2];
  uint64_t rooks[2];
  uint64_t queens[2];
  uint64_t king[2];
};

#endif