#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>
#include <stack>

#include "Move.h"

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
  castlingRights,
  notAPiece
};
struct prevMoveInfo {
  Move prevMove;
  uint64_t prevEP;
  uint64_t prevCastlingRights;
  piece prevCaptured;
  unsigned short prevHalfClock;
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
    color getTurn() const;
    unsigned short getHalfClock() const;
    unsigned short getFullCounter() const;

    int makeMove(Move m);
    void unMakeMove();

  private:
    piece getPieceAt(uint64_t pos);
    void movePiece(uint64_t from, uint64_t to, piece p);
    void takePiece(uint64_t from, uint64_t to, piece p);
    void takeEnPassat(uint64_t from, uint64_t to, piece p);
    void promotePawn(uint64_t pos, piece newP);
    // false = kingside, q = queenside
    void castle(bool qSide);

    void undoCapture(uint64_t pos, piece captured, color c);
    void undoCastle(bool qSide);
    void demotePawn(uint64_t prevFrom, uint64_t prevTo, piece newP);

    uint64_t m_colors[2];
    uint64_t m_pieces[8];

    color m_turn;
    unsigned short m_halfClock;
    unsigned short m_fullCounter;
    
    std::stack<prevMoveInfo> m_prevMoves;
};


#endif