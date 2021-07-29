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
    uint64_t getAllPieces();
    uint64_t getEmptySquares();
    uint64_t getWhitePieces();
    uint64_t getWhitePawns();
    uint64_t getWhiteKnights();
    uint64_t getWhiteRooks();
    uint64_t getWhiteBishops();
    uint64_t getWhiteQueens();
    uint64_t getWhiteKing();
    uint64_t getBlackPieces();
    uint64_t getBlackPawns();
    uint64_t getBlackKnights();
    uint64_t getBlackRooks();
    uint64_t getBlackBishops();
    uint64_t getBlackQueens();
    uint64_t getBlackKing();

  private:
    uint64_t m_boards[8];
};


#endif