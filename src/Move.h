#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>

class Move {
  public:
    Move(uint16_t from, uint16_t to, uint16_t flag);
    uint16_t getFrom();
    uint16_t getTo();
    uint16_t getFlag();

  private:
    uint16_t m_move;
};

#endif