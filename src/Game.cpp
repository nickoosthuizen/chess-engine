#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "Game.h"
#include "Board.h"
#include "moveGen.h"
#include "utilFunctions.h"
#include "perft.h"
#include "evaluate.h"


void Game::handleInput() {
  std::vector<std::string> words;
  while (true) {
    std::string input;
    getline(std::cin, input);
    
    split(input, " ", words);
    if (words.size() == 0) continue;

    if (words[0] == "display") {
      display();
    }
    else if (words[0] == "suggest") {
      suggestMove();
    }
    else if (words[0] == "play") {
      play();
    }

    if (words.size() < 2) continue;

    if (words[0] == "fen") {
      handleNewFen(input.substr(4, std::string::npos));
    }
    else if (words[0] == "move") {
      handleMove(words[1]);
    }
    else if (words[0] == "perft") {
      if (isWholeNumber(words[1])) {
        int depth = stoi(words[1]);
        std::cout << "Nodes searched: " << perft(depth, m_state) << std::endl;
      }
      else {
        std::cout << "Invalid depth" << std::endl;
      }
      std::cout << std::endl;
    }
    else if (words[0] == "divide") {
      if (isWholeNumber(words[1])) {
        int depth = stoi(words[1]);
        divide(depth, m_state);
      }
      else {
        std::cout << "Invalid depth" << std::endl;
      }
      std::cout << std::endl;
    }
  }
}

void Game::handleNewFen(std::string fen) {
  if (isValidFen(fen)) {
    m_state = Board(fen);
    m_history.clear();
  }
  else {
    std::cout << "FEN string is incorrect" << std::endl;
  }

  std::cout << std::endl;
}

void Game::handleMove(std::string m) {
  std::vector<Move> moves;
  std::vector<std::string> moveStrings;
  generateMoves(moves, m_state);
  int i;
  for (i = 0; i < moves.size(); ++i) {
    if (moves[i].toString() == m) break;
  }

  if (i < moves.size()) {
    color turn = m_state.getTurn();
    m_state.makeMove(moves[i]);
    if (isInCheck(m_state, turn)) {
      std::cout << "Move leaves king in check" << std::endl;
      m_state.unMakeMove();
    }
    else {
      m_state.unMakeMove();
      m_history.push_back(m_state);
      m_state.makeMove(moves[i]);
    }
  }
  else {
    std::cout << "Invalid move" << std::endl;
  }
  std::cout << std::endl;
}

void Game::display() {
  std::string fen = m_state.toFen();
  std::vector<std::string> fields;
  std::vector<std::string> rows;
  split(fen, " ", fields);
  split(fields[0], "/", rows);

  int emptyCounter;
  for (int i = 0; i < 8; ++i) {
    std::cout << "-----------------" << std::endl;
    std::cout << "|";
    for (int j = 0; j < rows[i].size(); ++j) {
      if (isdigit(rows[i][j])) {
        emptyCounter = rows[i][j] - '0';
        for (int k = 0; k < emptyCounter; ++k) {
          std::cout << " |";
        }
      }
      else {
        std::cout << rows[i][j] << "|";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "-----------------" << std::endl;

  std::cout << "Turn to Move: " << fields[1] << std::endl;
  std::cout << "Castling Rights: " << fields[2] << std::endl;
  std::cout << "Square currently en passat: " << fields[3] << std::endl;
  std::cout << "Half Move Counter: " << fields[4] << std::endl;
  std::cout << "Full Move Counter: " << fields[5] << std::endl;
  std::cout << std::endl;
}

void Game::suggestMove() {
  Move best = pickMove(m_state, 5);
  std::cout << "engine suggests: " << best.toString() << std::endl;
}

void Game::play() {
  Move aimove;
  std::string input;
  GameState status;
  std::cout << "Starting Game" << std::endl;
  
  while((status = getGameState()) == ongoing) {
    display();
    if (m_state.getTurn() == white) {
      std::cout << "Enter Move: " << std::endl;
      getline(std::cin, input);
      handleMove(input);
    }
    else {
      m_history.push_back(m_state);
      aimove = pickMove(m_state, 5);
      m_state.makeMove(aimove);
    }
  }

  if (status == draw) {
    std::cout << "Draw" << std::endl;
  }
  else if (status == stalemate) {
    std::cout << "Stalemate" << std::endl;
  }
  else if (status == checkmate) {
    std::string winner = (m_state.getTurn() == white) ? "black" : "white";
    std::cout << winner << " wins" << std::endl;
  }

  m_state = Board();
  m_history.clear();
}

GameState Game::getGameState() {
  if (75 <= m_state.getHalfClock()) return draw;

  std::vector<Move> moves;
  generateMoves(moves, m_state);
  bool movesAvailable = false;

  color turn = m_state.getTurn();
  for (int i = 0; i < moves.size(); ++i) {
    m_state.makeMove(moves[i]);
    if (!isInCheck(m_state, turn)) {
      movesAvailable = true;
      m_state.unMakeMove();
      break;
    }
    m_state.unMakeMove();
  }

  if (movesAvailable) return ongoing;
  else {
    if (isInCheck(m_state, turn)) return checkmate;
    else return stalemate;
  }
}