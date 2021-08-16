#ifndef EVALUATE_H
#define EVALUATE_H

#include <functional>
#include <utility>
#include <vector>

#include "Board.h"
#include "Move.h"

int miniMaxAlphaBeta(Board& state, int alpha, int beta, bool isMax, unsigned int maxDepth, std::function<int(const Board& b)> eval);
Move pickMove(Board& state, unsigned int maxDepth, std::function<int(const Board& b)> eval);

#endif