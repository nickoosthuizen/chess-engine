#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "Board.h"

enum GameState {
  ongoing, 
  checkmate,
  stalemate,
  draw
};    
class Game {
  public:
    void handleInput();
    void handleNewFen(std::string input);
    void handleMove(std::string input);
    void suggestMove();
    void display();
    void play();
    GameState getGameState();

  private:
    Board m_state;
    std::vector<Board> m_history;
    
};

#endif