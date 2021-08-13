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

uint16_t Move::getFrom() const { return (m_move >> 6) & 0x3F; }
uint16_t Move::getTo() const { return m_move & 0x3F; }
uint16_t Move::getFlag() const { return (m_move >> 12) & 0x0F; }
bool Move::isNone() const { return m_move == 0; }

std::string Move::toString() {
  std::string out = "";
  uint16_t flag = getFlag();
  switch (flag) {
    case REGULAR:
      out += "R ";
      break;
    case DOUBLE_PAWN:
      out += "DP ";
      break;
    case K_CASTLE:
      return "KC";
      break;
    case Q_CASTLE:
      return "QC";
      break;
    case CAPTURE:
      out += "C ";
      break;
    case EP_CAPTURE:
      out += "EPC ";
      break;
    case KN_PRMT:
      out += "KNP ";
      break;
    case B_PRMT:
      out += "BP ";
      break;
    case R_PRMT:
      out += "RP ";
      break;
    case Q_PRMT:
      out += "QP ";
      break;
    case KN_PRMT_CAPT:
      out += "KPC ";
      break;
    case B_PRMT_CAPT:
      out += "BPC ";
      break;
    case R_PRMT_CAPT:
      out += "RPC ";
      break;
    case Q_PRMT_CAPT:
      out += "QPC ";
      break;
  }

  out += posToSquare(getFrom());
  out += posToSquare(getTo());
  return out;
}