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
  kings,
  // only one side can have an enPassat pawn at a time
  enPassat
};

class Board {
  public:
    Board();
    bool operator==(const Board& other) const;

    uint64_t getAllPieces() const;
    uint64_t getEmptySquares() const;
    uint64_t getBByPiece(piece p) const;
    uint64_t getBByColor(color c) const;
    uint64_t getBByPieceAndColor(piece p, color c) const;
    
    // Testing functions
    void setColor(uint64_t b, color c);
    void setPiece(uint64_t b, piece p);
    void setCastling(bool val, color c);
    void clear();

    void movePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void takePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);

  private:
    uint64_t m_colors[2];
    uint64_t m_pieces[7];
    bool m_hasCastled[2];
};


#endif