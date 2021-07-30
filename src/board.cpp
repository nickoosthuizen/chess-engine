#include "board.h"
#include <cstdint>

uint64_t board::getAllPieces() { return m_boards[white] & m_boards[black]; }
uint64_t board::getEmptySquares() { return !(m_boards[white] & m_boards[black]); }
uint64_t board::getBByType(boardType t) { return m_boards[t]; }
uint64_t board::getBByTypeAndColor(boardType t, boardType c) { return m_boards[t] & m_boards[c]; }