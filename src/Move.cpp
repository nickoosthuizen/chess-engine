#include <stdint.h>

#include "Move.h"

Move::Move() {
  m_move = 0;
}

Move::Move(uint16_t from, uint16_t to, uint16_t flag) {
  m_move = (flag << 12) | (from << 6) | to;
}

uint16_t Move::getFrom() const { return (m_move >> 6) & 0x3F; }
uint16_t Move::getTo() const { return m_move & 0x3F; }
uint16_t Move::getFlag() const { return (m_move >> 12) & 0x0F; }