#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include <string>

class Move {
  public:
    Move();
    Move(uint16_t from, uint16_t to, uint16_t flag);
    bool operator==(const Move& other) const;

    inline uint16_t getFrom() const { return (m_move >> 6) & 0x3F; }
    inline uint16_t getTo() const { return m_move & 0x3F; }
    inline uint16_t getFlag() const { return (m_move >> 12) & 0x0F; }
    inline bool isNone() const { return m_move == 0; }
    
    std::string toString();

  private:
    uint16_t m_move;
};

#endif