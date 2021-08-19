#ifndef MOVE_GEN_LOOKUP_TBL
#define MOVE_GEN_LOOKUP_TBL

#include <cstdint>

#include "Board.h"

class MoveGenLookupTbl {
  public:
    MoveGenLookupTbl();
    inline uint64_t getPieceMove(uint16_t pos, piece p) const { return m_pieceMoveLookupTbl[p][pos]; }
    inline uint64_t getBlocked(uint16_t origin, uint16_t blocker) const { return m_blockedLookupTbl[origin][blocker]; }
    inline uint64_t getMovesWithoutEnd(uint16_t pos, piece p) const { return m_removePieceEndTbl[p][pos]; }
  
  private:
    void initPieceLookupTbl();
    void initBeyondLookupTbl();
    void initRemoveLookupTbl();

    uint64_t m_pieceMoveLookupTbl[6][64];
    uint64_t m_removePieceEndTbl[6][64];
    uint64_t m_blockedLookupTbl[64][64];
};

#endif