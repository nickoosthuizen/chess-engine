#include <cstdint>

#include "board.h"
#include "constants.h"

board::board() {
  m_boards[white] = WHITE_START;
  m_boards[black] = BLACK_START;
  m_boards[pawns] = PAWN_START;
  m_boards[knights] = KNIGHT_START;
  m_boards[rooks] = ROOK_START;
  m_boards[bishops] = BISHOP_START;
  m_boards[queens] = QUEEN_START;
  m_boards[kings] = KING_START;
}

uint64_t board::getAllPieces() { return m_boards[white] | m_boards[black]; }
uint64_t board::getEmptySquares() { return ~(m_boards[white] | m_boards[black]); }
uint64_t board::getBByType(boardType t) { return m_boards[t]; }
uint64_t board::getBByTypeAndColor(boardType t, boardType c) { return m_boards[t] & m_boards[c]; }