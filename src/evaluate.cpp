
#include <functional>
#include <vector>
#include <climits>

#include "evaluate.h"
#include "Board.h"
#include "Move.h"
#include "moveGen.h"
#include "constants.h"
#include "utilFunctions.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, color side, unsigned int maxDepth, std::function<int(const Board&, color)> eval) {
  int curScore, bestScore;
  bool movesAvailable = false;

  if (beta < alpha) return isMax ? alpha : beta;

  color turn = state.getTurn();

  std::vector<Move> moves;
  generateMoves(moves, state);

  if (maxDepth == 0) {
    for (int i = 0; i < moves.size(); ++i) {
      state.makeMove(moves[i]);
      if (!isInCheck(state, turn)) {
        movesAvailable = true;
        curScore = eval(state, side);
        if ((isMax && bestScore < curScore) || (!isMax && curScore < bestScore)) {
          bestScore = curScore;
        }   
      }
      state.unMakeMove();
    }
    return (!movesAvailable) ? noMovesAvailable(state, side) : bestScore;
  }

  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      movesAvailable = true;
      curScore = miniMaxAlphaBeta(state, alpha, beta, !isMax, side, maxDepth - 1, eval);
      if (isMax && alpha < curScore) alpha = curScore;
      else if (!isMax && curScore < beta) beta = curScore;
    }
    state.unMakeMove();
  }

  if (!movesAvailable) {
    return noMovesAvailable(state, side);
  }
  else {
    return isMax ? alpha : beta;  
  }
}

Move pickMove(Board& state, unsigned int maxDepth, std::function<int(const Board&, color)> eval) {
  Move bestMove;
  int bestScore, curScore;

  color turn = state.getTurn();

  std::vector<Move> moves;
  generateMoves(moves, state);

  bestScore = INT_MIN;
  bestMove = Move();
  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      curScore = miniMaxAlphaBeta(state, bestScore, INT_MAX, false, state.getTurn(), maxDepth - 1, eval);
      if (bestScore < curScore) {
        bestScore = curScore;
        bestMove = moves[i];
      }
    }
    state.unMakeMove();
  }

  return bestMove;
}

int noMovesAvailable(const Board& b, color side) {
  color turn = b.getTurn();
  if (isInCheck(b, turn)) {
    if (turn == side) {
      return CHECK_MATE_LOSE;
    }
    else {
      return CHECK_MATE_WIN;
    }
  }
  else {
    return DRAW_VAL;
  }
}

int pieceCountScore(const Board& b, color side) {
  return ((populationCount(b.getBByPieceAndColor(pawns, side)) * PAWN_VAL) + 
          (populationCount(b.getBByPieceAndColor(knights, side)) * KNIGHT_VAL) + 
          (populationCount(b.getBByPieceAndColor(bishops, side)) * BISHOP_VAL) + 
          (populationCount(b.getBByPieceAndColor(rooks, side)) * ROOK_VAL) + 
          (populationCount(b.getBByPieceAndColor(queens, side)) * QUEEN_VAL));
}