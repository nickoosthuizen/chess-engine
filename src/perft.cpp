#include <vector>
#include <iostream>
#include <numeric>
#include <assert.h>

#include "perft.h"
#include "board.h"
#include "moveGen.h"

unsigned int perft(int depth, Board& b) {
  unsigned int totalMoves = 0;
  color turn = b.getTurn();
  Board verify = b;

  if (depth == 0) {
    return 1;
  }

  std::vector<Move> moves = generateMoves(b);

  for (int i = 0; i < moves.size(); ++i) {
    b.makeMove(moves[i]);
    if (!isInCheck(b, turn)) {
      totalMoves += perft(depth - 1, b);
    }
    b.unMakeMove();
    assert (b == verify);
  }
  return totalMoves;
}

void divide(int depth, Board& b) {
  if (depth == 0) return;
  color turn = b.getTurn();

  std::vector<Move> moves = generateMoves(b);
  std::vector<int> numMovesProduced; 
  
  for (int i = 0; i < moves.size(); ++i) {
    b.makeMove(moves[i]);
    if (!isInCheck(b, turn)) {
      numMovesProduced.push_back(perft(depth - 1, b));
    }
    b.unMakeMove();
  }

  for (int i = 0; i < numMovesProduced.size(); ++i) {
    std::cout << moves[i].toString() << ": " << numMovesProduced[i] << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Nodes Searched: " << accumulate(numMovesProduced.begin(), numMovesProduced.end(), 0) << std::endl;
}