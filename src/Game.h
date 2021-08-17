#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "Board.h"

class Game {
  public:
    void handleInput();
    void handleNewFen(std::string input);
    void handleMove(std::string input);
    void suggestMove();
    void display();

  private:
    Board m_state;
    std::vector<Board> m_history;
    
};

#endif