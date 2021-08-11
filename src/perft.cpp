#include <vector>

#include "perft.h"
#include "board.h"
#include "moveGen.h"

unsigned int perft(int depth, Board b) {
  unsigned int totalMoves = 0;

  if (depth == 0) {
    return 0;
  }

  std::vector<Board> moves;
  generateMoves(moves, b);
  totalMoves += moves.size();
  for (int i = 0; i < moves.size(); ++i) {
    totalMoves += perft(depth - 1, moves[i]);
  }
  return totalMoves;
}

unsigned int divide(int depth, Board b) {
  
}