#include <vector>
#include <climits>

#include "evaluate.h"
#include "Board.h"
#include "Move.h"
#include "moveGen.h"
#include "constants.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, color side, unsigned int maxDepth) {
  int curScore, bestScore;
  bool movesAvailable = false;

  if (beta < alpha) return isMax ? alpha : beta;

  color turn = state.getTurn();

  if (maxDepth == 0) {
    return pieceCountScore(state, side);
  }

  std::vector<Move> moves;
  generateMoves(moves, state);

  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      movesAvailable = true;
      curScore = miniMaxAlphaBeta(state, alpha, beta, !isMax, side, maxDepth - 1);
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

Move pickMove(Board& state, unsigned int maxDepth) {
  Move bestMove;
  int bestScore, curScore;

  color turn = state.getTurn();

  std::vector<Move> moves;
  generateMoves(moves, state);

  bestScore = INT_MIN;
  for (int i = 0; i < moves.size(); ++i) {
    state.makeMove(moves[i]);
    if (!isInCheck(state, turn)) {
      curScore = miniMaxAlphaBeta(state, bestScore, INT_MAX, false, turn, maxDepth - 1);
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
  color opposing = side == white ? black : white;
  return (((b.getPieceCount(pawns, side) - b.getPieceCount(pawns, opposing)) * PAWN_VAL) + 
          ((b.getPieceCount(knights, side) - b.getPieceCount(knights, opposing)) * KNIGHT_VAL) + 
          ((b.getPieceCount(bishops, side) - b.getPieceCount(bishops, opposing)) * BISHOP_VAL) + 
          ((b.getPieceCount(rooks, side) - b.getPieceCount(rooks, opposing))* ROOK_VAL) + 
          ((b.getPieceCount(queens, side) - b.getPieceCount(queens, opposing)) * QUEEN_VAL));
}