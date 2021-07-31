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