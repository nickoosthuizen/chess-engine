#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>

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
    // A board can be initialized with a board string in FEN format
    Board(std::string fen);
    bool operator==(const Board& other) const;

    uint64_t getAllPieces() const;
    uint64_t getEmptySquares() const;
    uint64_t getBByPiece(piece p) const;
    uint64_t getBByColor(color c) const;
    uint64_t getBByPieceAndColor(piece p, color c) const;
    color getTurn();
    unsigned short getHalfClock() const;
    unsigned short getFullCounter() const;
    
    void setColor(uint64_t b, color c);
    void setPiece(uint64_t b, piece p);
    void clear();

    void movePiece(uint64_t oldPos, uint64_t newPos, piece p);
    void takePiece(uint64_t oldPos, uint64_t newPos, piece p);
    void takeEnPassat(uint64_t oldPos, uint64_t newPos, piece p);
    void promotePawn(uint64_t pos, piece newP);
    // false = kingside, q = queenside
    void castle(bool kq);

  private:
    uint64_t m_colors[2];
    uint64_t m_pieces[8];
    // 0 or false = white, 1 or true = black
    color m_turn;
    unsigned short m_halfClock;
    unsigned short m_fullCounter;
};


#endif