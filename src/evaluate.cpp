
#include <functional>
#include <vector>

#include "Board.h"
#include "Move.h"
#include "moveGen.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, unsigned int maxDepth, std::function<int(const Board& b)> eval) {
  int curScore, bestScore;

  if (beta < alpha) return isMax ? alpha : beta;

  color turn = state.getTurn();

  std::vector<Move> moves;
  generateMoves(moves, state);

  if (maxDepth == 0) {
    for (int i = 0; i < moves.size(); ++i) {
      state.makeMove(moves[i]);
      if (!isInCheck(state, turn)) {
        curScore = eval(state);
        if ((isMax && bestScore < curScore) || (!isMax && curScore < bestScore)) bestScore = curScore;   
      }
      state.unMakeMove();
    }
    return bestScore;
  }

  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      curScore = miniMaxAlphaBeta(state, alpha, beta, !isMax, maxDepth - 1, eval);
      if (isMax && alpha < curScore) alpha = curScore;
      else if (!isMax && curScore < beta) beta = curScore;
    }
    state.unMakeMove(moves[i]);
  }

  isMax ? return alpha : return beta;
}

Move pickMove(Board& state, unsigned int maxDepth, std::function<int(const Board& b)> eval) {
  Move bestMove;
  int bestScore, curScore;

  color turn = state.getTurn();

  std::vector<Move> moves;
  generateMoves(moves, state);

  if (moves.size() < 1) {
    return Move();
  }

  bestScore = -1000000;
  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      curScore = miniMaxAlphaBeta(state, bestScore, 1000000, false, maxDepth - 1, eval);
      if (bestScore < curScore) {
        bestScore = curScore;
        bestMove = moves[i];
      }
    }
    state.unMakeMove();
  }
  return bestMove;
}