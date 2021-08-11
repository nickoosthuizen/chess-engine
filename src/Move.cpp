#include <stdint.h>

#include "Move.h"

Move::Move(uint16_t from, uint16_t to, uint16_t flag) {
  m_move = (flag << 12) | (from << 6) | to;
}

uint16_t Move::getFrom() { return (m_move >> 6) & 0x3F; }
uint16_t Move::getTo() { return m_move & 0x3F; }
uint16_t Move::getFlag() { return (m_move >> 12) & 0x0F; }