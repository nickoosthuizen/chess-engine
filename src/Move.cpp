#include <stdint.h>
#include <string>

#include "Move.h"
#include "constants.h"
#include "utilFunctions.h"

Move::Move() {
  m_move = 0;
}

Move::Move(uint16_t from, uint16_t to, uint16_t flag) {
  m_move = (flag << 12) | (from << 6) | to;
}

bool Move::operator==(const Move& other) const {
  return m_move == other.m_move;
}

std::string Move::toString() {
  std::string output = posToSquare(getFrom()) + posToSquare(getTo());
  switch(getFlag()) {
    case KN_PRMT:
    case KN_PRMT_CAPT:
      output += "n";
      break;
    case B_PRMT:
    case B_PRMT_CAPT:
      output += "b";
      break;
    case R_PRMT:
    case R_PRMT_CAPT:
      output += "r";
      break;
    case Q_PRMT:
    case Q_PRMT_CAPT:
      output += "q";
      break;
  }
  return output;
}