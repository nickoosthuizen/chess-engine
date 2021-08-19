#include <vector>

#include "moveGen.h"
#include "board.h"
#include "constants.h"
#include "utilFunctions.h"
#include "Move.h"
#include "MoveGenLookupTbl.h"
#include "pieceShifts.h"

MoveGenLookupTbl lookup;

std::vector<Move> generateMoves(const Board& b) {
  color c = b.getTurn();

  struct BoardDetails d = { 
                            b.getEmptySquares(), 
                            b.getBByColor(c == white ? black : white), 
                            b.getAllPieces(),
                            b.getBByPiece(enPassat)
                          };

  std::vector<Move> newMoves;

  if (b.getBByPieceAndColor(pawns, c)) {
    generatePawnMoves(newMoves, b.getBByPieceAndColor(pawns, c), c, d);
  }
  if (b.getBByPieceAndColor(knights, c)) {
    generatePieceMoves(newMoves, b.getBByPieceAndColor(knights, c), knights, d);
  }
  if (b.getBByPieceAndColor(bishops, c)) {
    generatePieceMoves(newMoves, b.getBByPieceAndColor(bishops, c), bishops, d);
  }
  if (b.getBByPieceAndColor(rooks, c)) {
    generatePieceMoves(newMoves, b.getBByPieceAndColor(rooks, c), rooks, d);
  }
  if (b.getBByPieceAndColor(queens, c)) {
    generatePieceMoves(newMoves, b.getBByPieceAndColor(queens, c), queens, d);
  }
  if (b.getBByPieceAndColor(kings, c)) {
    generatePieceMoves(newMoves, b.getBByPieceAndColor(kings, c), kings, d);
  }
  if (b.getBByPieceAndColor(castlingRights, c)) {
    generateCastleMoves(newMoves, b);
  }
  return newMoves;
}

bool isInCheck(const Board& b, color side) {
  return areSquaresAttacked(b, side == white ? black : white, b.getBByPieceAndColor(kings, side));
}

uint64_t generatePieceMoveBoard(uint16_t pos, piece p, uint64_t blockers) {
  uint64_t moveBoard = lookup.getPieceMove(pos, p);
  uint64_t individualBlocker;
  for (blockers &= lookup.getMovesWithoutEnd(pos, p); blockers != 0; blockers = (blockers ^ individualBlocker) & moveBoard) {
    individualBlocker = getLSB(blockers);
    moveBoard &= ~lookup.getBlocked(pos, bitBoardToPos(individualBlocker));
  }
  return moveBoard;
}

void generatePieceMoves(std::vector<Move>& moves, uint64_t pieces, piece p, const struct BoardDetails& d) {
  uint64_t moveBoard, attacks, pushes;
  uint16_t from;
  
  for (uint64_t individualPiece; pieces != 0; pieces ^= individualPiece) {
    individualPiece = getLSB(pieces);
    from = bitBoardToPos(individualPiece);
    moveBoard = generatePieceMoveBoard(from, p, d.allPieces);
    attacks = moveBoard & d.opposingPieces;
    pushes = moveBoard & d.empty;
    if (attacks & d.ep) {
      moves.push_back(Move(from, bitBoardToPos(d.ep), EP_CAPTURE));
      attacks ^= d.ep;
    }
    for (uint64_t individualAttack; attacks != 0; attacks ^= individualAttack) {
      individualAttack = getLSB(attacks);
      moves.push_back(Move(from, bitBoardToPos(individualAttack), CAPTURE));
    }
    for (uint64_t individualPush; pushes != 0; pushes ^= individualPush) {
      individualPush = getLSB(pushes);
      moves.push_back(Move(from, bitBoardToPos(individualPush), REGULAR));
    }
  }
}

uint64_t generateTotalPieceMoveBoard(uint64_t pieces, piece p, uint64_t blockers) {
  uint64_t totalMoveBoard = 0;
  for (uint64_t individualPiece; pieces != 0; pieces ^= individualPiece) {
    individualPiece = getLSB(pieces);
    totalMoveBoard |= generatePieceMoveBoard(bitBoardToPos(individualPiece), p, blockers);
  }
  return totalMoveBoard;
} 

void generatePawnMoves(std::vector<Move>& moves, uint64_t allPawns, color c, const struct BoardDetails& d) {
  uint64_t attacks, onePush, twoPush;
  uint16_t from;

  for (uint64_t individualPawn; allPawns != 0; allPawns ^= individualPawn) {
    individualPawn = getLSB(allPawns);
    from = bitBoardToPos(individualPawn);

    if (c == white) {
      attacks = whitePawnAttack(individualPawn, d.opposingPieces | d.ep);
      onePush = whitePawnPush(individualPawn, d.empty);
      twoPush = whitePawnPushTwo(individualPawn, d.empty);
    }
    else {
      attacks = blackPawnAttack(individualPawn, d.opposingPieces | d.ep);
      onePush = blackPawnPush(individualPawn, d.empty);
      twoPush = blackPawnPushTwo(individualPawn, d.empty);
    }

    if (attacks & d.ep) {
      moves.push_back(Move(from, bitBoardToPos(d.ep), EP_CAPTURE));
      attacks ^= d.ep;
    }

    if ((c == white && (individualPawn & RANK_7)) || (c == black && (individualPawn & RANK_2))) {
      uint16_t to;
      for (uint64_t individualAttack; attacks != 0; attacks ^= individualAttack) {
        individualAttack = getLSB(attacks);
        to = bitBoardToPos(individualAttack);
        moves.push_back(Move(from, to, Q_PRMT_CAPT));
        moves.push_back(Move(from, to, KN_PRMT_CAPT));
        moves.push_back(Move(from, to, R_PRMT_CAPT));
        moves.push_back(Move(from, to, B_PRMT_CAPT));
      }
      if (onePush) {
        to = bitBoardToPos(onePush);
        moves.push_back(Move(from, to, Q_PRMT));
        moves.push_back(Move(from, to, KN_PRMT));
        moves.push_back(Move(from, to, R_PRMT));
        moves.push_back(Move(from, to, B_PRMT));
      }
    }
    else {
      for (uint64_t individualAttack; attacks != 0; attacks ^= individualAttack) {
        individualAttack = getLSB(attacks);
        moves.push_back(Move(from, bitBoardToPos(individualAttack), CAPTURE));
      }
      if (twoPush) {
        moves.push_back(Move(from, bitBoardToPos(twoPush), DOUBLE_PAWN));
      }
      if (onePush) {
        moves.push_back(Move(from, bitBoardToPos(onePush), REGULAR));
      }
    }
  }
}

void generateCastleMoves(std::vector<Move>& moves, const Board& b) {
  uint16_t kingPos, qSidePos, kSidePos;
  color opponent, c;
  uint64_t rank, allPieces;
  
  c = b.getTurn();
  allPieces = b.getAllPieces();

  if (c == white) {
    opponent = black;
    rank = RANK_1;
    kingPos = 3;
    qSidePos = 5;
    kSidePos = 1;
  }
  else {
    opponent = white;
    rank = RANK_8;
    kingPos = 59;
    qSidePos = 61;
    kSidePos = 57;
  }

  if ((b.getBByPieceAndColor(castlingRights, c) & FILE_A) 
        && !(allPieces & (Q_SIDE_BTWN_K_AND_R & rank))
        && !(areSquaresAttacked(b, opponent, Q_SIDE_VULN_SQUARES & rank))) {
    moves.push_back(Move(kingPos, qSidePos, Q_CASTLE));
  }
  if ((b.getBByPieceAndColor(castlingRights, c) & FILE_H) 
        && !(allPieces & (K_SIDE_BTWN_K_AND_R & rank))
        && !(areSquaresAttacked(b, opponent, K_SIDE_VULN_SQUARES & rank))) {
    moves.push_back(Move(kingPos, kSidePos, K_CASTLE));
  }
  return;
}

bool areSquaresAttacked(const Board& b, color attacker, uint64_t squares) {
  uint64_t blockers = b.getAllPieces();
  if (attacker == white) {
    if (whitePawnAttack(b.getBByPieceAndColor(pawns, attacker), squares)) return true;
  }
  else {
    if (blackPawnAttack(b.getBByPieceAndColor(pawns, attacker), squares)) return true;
  }

  if (generateTotalPieceMoveBoard(b.getBByPieceAndColor(knights, attacker), knights, blockers) & squares) return true;
  if (generateTotalPieceMoveBoard(b.getBByPieceAndColor(bishops, attacker), bishops, blockers) & squares) return true;
  if (generateTotalPieceMoveBoard(b.getBByPieceAndColor(rooks, attacker), rooks, blockers) & squares) return true;
  if (generateTotalPieceMoveBoard(b.getBByPieceAndColor(queens, attacker), queens, blockers) & squares) return true;
  if (generateTotalPieceMoveBoard(b.getBByPieceAndColor(kings, attacker), kings, blockers) & squares) return true;
  return false;
}