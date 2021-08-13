#include <vector>
#include <iostream>

#include "perft.h"
#include "board.h"
#include "moveGen.h"

unsigned int perft(int depth, Board b) {
  unsigned int totalMoves = 0;

  if (depth == 0) {
    return 0;
  }

  std::vector<Move> moves;
  generateMoves(moves, b);
  totalMoves += moves.size();
  for (int i = 0; i < moves.size(); ++i) {
    b.makeMove(moves[i]);
    totalMoves += perft(depth - 1, b);
    b.unMakeMove();
  }
  return totalMoves;
}

void divide(int depth, Board b) {
  if (depth == 0) return;

  std::vector<Move> moves;
  std::vector<int> numMovesProduced;
  generateMoves(moves, b);
  
  for (int i = 0; i < moves.size(); ++i) {
    b.makeMove(moves[i]);
    numMovesProduced.push_back(perft(depth - 1, b));
    b.unMakeMove();
  }

  std::cout << "Move | NodesProduced" << std::endl;

  for (int i = 0; i < moves.size(); ++i) {
    std::cout << moves[i].toString() << " | " << numMovesProduced[i] << std::endl;
  }
}