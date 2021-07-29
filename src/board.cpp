#include "board.h"
#include <cstdint>

uint64_t board::getAllPieces() { return m_boards[white] & m_boards[black]; }
uint64_t board::getEmptySquares() { return !(m_boards[white] & m_boards[black]); }
uint64_t board::getWhitePieces() { return m_boards[white]; }
uint64_t board::getWhitePawns() { return m_boards[white] & m_boards[pawns]; }
uint64_t board::getWhiteKnights() { return m_boards[white] & m_boards[knights]; }
uint64_t board::getWhiteRooks() { return m_boards[white] & m_boards[rooks]; }
uint64_t board::getWhiteBishops() { return m_boards[white] & m_boards[bishops]; }
uint64_t board::getWhiteQueens() { return m_boards[white] & m_boards[queens]; }
uint64_t board::getWhiteKing() { return m_boards[white] & m_boards[kings]; }
uint64_t board::getBlackPieces() { return m_boards[black]; }
uint64_t board::getBlackPawns() { return m_boards[black] & m_boards[pawns]; }
uint64_t board::getBlackKnights() { return m_boards[black] & m_boards[knights]; }
uint64_t board::getBlackRooks() { return m_boards[black] & m_boards[rooks]; }
uint64_t board::getBlackBishops() { return m_boards[black] & m_boards[bishops]; }
uint64_t board::getBlackQueens() { return m_boards[black] & m_boards[queens]; }
uint64_t board::getBlackKing() { return m_boards[black] & m_boards[kings]; }