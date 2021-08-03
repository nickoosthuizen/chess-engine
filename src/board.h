#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

enum color {
  white,
  black
};

enum piece {
  pawns,
  knights,
  rooks,
  bishops,
  queens,
  kings
};

class Board {
  public:
    Board();
    uint64_t getAllPieces();
    uint64_t getEmptySquares();
    uint64_t getBByPiece(piece p);
    uint64_t getBByColor(color c);
    uint64_t getBByPieceAndColor(piece p, color c);
    void movePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void takePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void setEnPassat(uint64_t b, color c);

  private:
    uint64_t m_colors[2];
    uint64_t m_pieces[6];
    uint64_t m_enPassat[2];
    bool m_hasCastled[2];
};


#endif