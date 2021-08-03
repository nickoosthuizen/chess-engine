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
  m_enPassat[white] = 0;
  m_enPassat[black] = 0;
  m_hasCastled[white] = false;
  m_hasCastled[black] = false;
}

uint64_t Board::getAllPieces() { return m_colors[white] | m_colors[black]; }
uint64_t Board::getEmptySquares() { return ~(m_colors[white] | m_colors[black]); }
uint64_t Board::getBByPiece(piece p) { return m_pieces[p]; }
uint64_t Board::getBByColor(color c) { return m_colors[c]; }
uint64_t Board::getBByPieceAndColor(piece p, color c) { return m_pieces[p] & m_colors[c]; }

void Board::movePiece(uint64_t oldPos, uint64_t newPos, piece p, color c) {
  m_pieces[p] ^= oldPos;
  m_pieces[p] |= newPos;
  m_colors[c] ^= oldPos;
  m_colors[c] |= newPos;
}

void Board::takePiece(uint64_t oldPos, uint64_t newPos, piece p, color c) {
  m_colors[!c] ^= newPos;
  for (int i = 0; i < 6; i++) {
    if (newPos & m_pieces[i]) {
      m_pieces[i] ^= newPos;
    }
  }
  movePiece(oldPos, newPos, p, c)
}

void Board::setEnPassat(uint64_t b, color c) { m_enPassat[c] = b; }