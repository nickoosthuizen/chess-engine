#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

enum boardType {
  white,
  black,
  pawns,
  knights,
  rooks,
  bishops,
  queens,
  kings
};

const uint64_t WHITE_START = 0x000000000000FFFF;
const uint64_t BLACK_START = 0xFFFF000000000000;
const uint64_t PAWN_START = 0x00FF00000000FF00;
const uint64_t KNIGHT_START = 0x4200000000000042;
const uint64_t ROOK_START = 0x8100000000000081;
const uint64_t BISHOP_START = 0x2400000000000024;
const uint64_t QUEEN_START = 0x1000000000000008;
const uint64_t KING_START = 0x0800000000000010;

class board {
  public:
    board();
    uint64_t getAllPieces();
    uint64_t getEmptySquares();
    uint64_t getBByType(boardType t);
    uint64_t getBByTypeAndColor(boardType t, boardType c);

  private:
    uint64_t m_boards[8];
};


#endif