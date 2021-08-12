#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>

class Move {
  public:
    Move();
    Move(uint16_t from, uint16_t to, uint16_t flag);
    uint16_t getFrom() const;
    uint16_t getTo() const;
    uint16_t getFlag() const;

  private:
    uint16_t m_move;
};

#endif