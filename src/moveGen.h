#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include <cstdint>
#include <vector>

#include "board.h"
#include "Move.h"
#include "MoveGenLookupTbl.h"

extern MoveGenLookupTbl lookup;
struct BoardDetails {
  uint64_t empty;
  uint64_t opposingPieces;
  uint64_t allPieces;
  uint64_t ep;
};

std::vector<Move> generateMoves(const Board& b);
bool isInCheck(const Board& b, color side);
    
uint64_t generatePieceMoveBoard(uint16_t loc, piece p, uint64_t blockers);
uint64_t generateTotalPieceMoveBoard(uint64_t pieces, piece p, uint64_t blockers);
void generatePieceMoves(std::vector<Move>& moves, uint64_t pieces, piece p, const struct BoardDetails& d);
void generatePawnMoves(std::vector<Move>& moves, uint64_t allPawns, color c, const struct BoardDetails& d);
void generateCastleMoves(std::vector<Move>& moves, const Board& b);

bool areSquaresAttacked(const Board& b, color defender, uint64_t squares);


#endif