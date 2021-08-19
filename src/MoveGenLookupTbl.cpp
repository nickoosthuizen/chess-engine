#include "MoveGenLookupTbl.h"
#include "pieceShifts.h"
#include "utilFunctions.h"
#include "constants.h"

MoveGenLookupTbl::MoveGenLookupTbl() {
  initPieceLookupTbl();
  initBeyondLookupTbl();
  initRemoveLookupTbl();
}

void MoveGenLookupTbl::initPieceLookupTbl() {
  uint64_t bd;

  for (int i = 0; i < 64; ++i) {
    bd = posToBitBoard(i);
    m_pieceMoveLookupTbl[pawns][i] = 0;
    m_pieceMoveLookupTbl[knights][i] = knightMove(bd);
    m_pieceMoveLookupTbl[bishops][i] = bishopMove(bd);
    m_pieceMoveLookupTbl[rooks][i] = rookMove(bd);
    m_pieceMoveLookupTbl[queens][i] = queenMove(bd);
    m_pieceMoveLookupTbl[kings][i] = kingMove(bd);
  }
}

void MoveGenLookupTbl::initBeyondLookupTbl() {
  uint64_t origin, blocker;

  for (int i = 0; i < 64; ++i) {
    origin = posToBitBoard(i);
    for (int j = 0; j < 64; j++) {
      blocker = posToBitBoard(j);
      if (ray(origin, oneNorth) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneNorth);
      }
      else if (ray(origin, oneSouth) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneSouth);
      }
      else if (ray(origin, oneWest) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneWest);
      }
      else if (ray(origin, oneEast) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneEast);
      }
      else if (ray(origin, oneNoWest) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneNoWest);
      }
      else if (ray(origin, oneNoEast) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneNoEast);
      }
      else if (ray(origin, oneSoWest) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneSoWest);
      }
      else if (ray(origin, oneSoEast) & blocker) {
        m_blockedLookupTbl[i][j] = ray(blocker, oneSoEast);
      }
      else {
        m_blockedLookupTbl[i][j] = 0;
      }
    }
  }
}

void MoveGenLookupTbl::initRemoveLookupTbl() {
  uint64_t b;
  for (int i = 0; i < 64; ++i) {
    b = posToBitBoard(i);
    m_removePieceEndTbl[pawns][i] = 0;
    m_removePieceEndTbl[knights][i] = 0;
    m_removePieceEndTbl[bishops][i] = m_pieceMoveLookupTbl[bishops][i] & ~(RANK_1 | RANK_8 | FILE_A | FILE_H);
    m_removePieceEndTbl[rooks][i] = (ray(b, oneNorth) & ~RANK_8) | (ray(b, oneSouth) & ~RANK_1) | (ray(b, oneWest) & ~FILE_A) | (ray(b, oneEast) & ~FILE_H);
    m_removePieceEndTbl[queens][i] = m_removePieceEndTbl[bishops][i] | m_removePieceEndTbl[rooks][i];
    m_removePieceEndTbl[kings][i] = 0;
  }
}