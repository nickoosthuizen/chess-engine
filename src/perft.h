#ifndef PERFT_H
#define PERFT_H

#include "Board.h"

unsigned int perft(int depth, Board b);
void divide(int depth, Board b);

#endif