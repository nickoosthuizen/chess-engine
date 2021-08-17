#ifndef EVALUATE_H
#define EVALUATE_H

#include <functional>
#include <utility>
#include <vector>

#include "Board.h"
#include "Move.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, color side, unsigned int maxDepth, std::function<int(const Board& b, color)> eval);
Move pickMove(Board& state, unsigned int maxDepth, std::function<int(const Board&, color)> eval);
int noMovesAvailable(const Board& b, color side);

int pieceCountScore(const Board& b, color);

#endif