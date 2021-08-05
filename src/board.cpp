#include <cstdint>

#include "board.h"
#include "constants.h"

Board::Board() {
  m_colors[white] = WHITE_START;
  m_colors[black] = BLACK_START;
  m_pieces[pawns] = PAWN_START;
  m_pieces[knights] = KNIGHT_START;
  m_pieces[rooks] = ROOK_START;
  m_pieces[bishops] = BISHOP_START;
  m_pieces[queens] = QUEEN_START;
  m_pieces[kings] = KING_START;
  m_pieces[enPassat] = 0;
  m_pieces[castlingRights] = KING_START | ROOK_START;
}

bool Board::operator==(const Board& other) const {
  return (m_colors[white] == other.m_colors[white]) &&
         (m_colors[black] == other.m_colors[black]) &&
         (m_pieces[pawns] == other.m_pieces[pawns]) &&
         (m_pieces[knights] == other.m_pieces[knights]) &&
         (m_pieces[rooks] == other.m_pieces[rooks]) &&
         (m_pieces[bishops] == other.m_pieces[bishops]) &&
         (m_pieces[queens] == other.m_pieces[queens]) &&
         (m_pieces[kings] == other.m_pieces[kings]) &&
         (m_pieces[enPassat] == other.m_pieces[enPassat]) &&
         (m_pieces[castlingRights] == m_pieces[castlingRights]);
}

uint64_t Board::getAllPieces() const { return m_colors[white] | m_colors[black]; }
uint64_t Board::getEmptySquares() const { return ~(m_colors[white] | m_colors[black]); }
uint64_t Board::getBByPiece(piece p) const { return m_pieces[p]; }
uint64_t Board::getBByColor(color c) const { return m_colors[c]; }
uint64_t Board::getBByPieceAndColor(piece p, color c) const { return m_pieces[p] & m_colors[c]; }

void Board::setColor(uint64_t b, color c) { m_colors[c] = b; }
void Board::setPiece(uint64_t b, piece p) { m_pieces[p] = b; }
void Board::clear() {
  m_colors[white] = 0;
  m_colors[black] = 0;
  m_pieces[pawns] = 0;
  m_pieces[knights] = 0;
  m_pieces[rooks] = 0;
  m_pieces[bishops] = 0;
  m_pieces[queens] = 0;
  m_pieces[kings] = 0;
  m_pieces[enPassat] = 0;
  m_pieces[castlingRights] = 0;
}

void Board::movePiece(uint64_t oldPos, uint64_t newPos, piece p, color c) {
  m_pieces[p] ^= oldPos;
  m_pieces[p] |= newPos;
  m_colors[c] ^= oldPos;
  m_colors[c] |= newPos;
  if (m_pieces[enPassat]) m_pieces[enPassat] = 0;
}

void Board::takePiece(uint64_t oldPos, uint64_t newPos, piece p, color c) {
  m_colors[!c] ^= newPos;
  for (int i = 0; i < 6; i++) {
    if (newPos & m_pieces[i]) {
      m_pieces[i] ^= newPos;
    }
  }
  movePiece(oldPos, newPos, p, c);
}

void Board::takeEnPassat(uint64_t oldPos, uint64_t newPos, piece p, color c) {
  uint64_t pawnPos = (c == white) ? m_pieces[enPassat] >> 8 : m_pieces[enPassat] << 8;
  m_colors[!c] ^= pawnPos;
  m_pieces[pawns] ^= pawnPos;
  movePiece(oldPos, newPos, p, c);
}

void Board::promotePawn(uint64_t pos, piece newP) {
  m_pieces[pawns] ^= pos;
  m_pieces[newP] |= pos; 
}