#ifndef EVALUATE_H
#define EVALUATE_H

#include <functional>
#include <utility>
#include <vector>

#include "Board.h"
#include "Move.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, color side, unsigned int maxDepth);
Move pickMove(Board& state, unsigned int maxDepth);
int noMovesAvailable(const Board& b, color side);

int pieceCountScore(const Board& b, color);

#endif