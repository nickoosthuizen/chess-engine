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
  enPassat,
  castlingRights
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
    void clear();

    void movePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void takePiece(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void takeEnPassat(uint64_t oldPos, uint64_t newPos, piece p, color c);
    void promotePawn(uint64_t pos, piece newP);

  private:
    uint64_t m_colors[2];
    uint64_t m_pieces[8];
};


#endif