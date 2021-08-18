#include <vector>
#include <functional>

#include "moveGen.h"
#include "board.h"
#include "constants.h"
#include "utilFunctions.h"
#include "Move.h"

/*
 * Ex: 000001000000 (hypothetical 12 bit unsigned integer)
 *    0000
 *    0100
 *    0000
 * 
 *    One north = 010000000000
 *    0100
 *    0000
 *    0000
 * 
 *    One East = 000000100000
 *    0000
 *    0010
 *    0000
 */

uint64_t whitePawnPush(uint64_t whitePawns, uint64_t empty) {
  return oneNorth(whitePawns) & empty;
}

uint64_t whitePawnPushTwo(uint64_t whitePawns, uint64_t empty) {
  uint64_t firstPush = oneNorth(whitePawns & RANK_2) & empty;
  return oneNorth(firstPush) & empty;
}

uint64_t blackPawnPush(uint64_t blackPawns, uint64_t empty) {
  return oneSouth(blackPawns) & empty;
}

uint64_t blackPawnPushTwo(uint64_t blackPawns, uint64_t empty) {
  uint64_t firstPush = oneSouth(blackPawns & RANK_7) & empty;
  return oneSouth(firstPush) & empty;
}

uint64_t whitePawnAttack(uint64_t whitePawns, uint64_t blackPieces) {
  return (oneNoWest(whitePawns) | oneNoEast(whitePawns)) & blackPieces;
}

uint64_t blackPawnAttack(uint64_t blackPawns, uint64_t whitePieces) {
  return (oneSoWest(blackPawns) | oneSoEast(blackPawns)) & whitePieces;
}

uint64_t knightMove(uint64_t knights, uint64_t empty, uint64_t pieces) {
  return knightLookupTable[bitBoardToPos(knights)] & (empty | pieces);
}

uint64_t multKnightMove(uint64_t knights, uint64_t empty, uint64_t pieces) {
  uint64_t knight, totalAttackBoard;
  totalAttackBoard = 0;
  while (knights) {
    knight = getLSB(knights);
    knights ^= knight;
    totalAttackBoard |= knightMove(knight, empty, pieces);
  }
  return totalAttackBoard;
}

uint64_t bishopMove(uint64_t bishops, uint64_t empty, uint64_t pieces) {
  uint64_t bishopMoveBoard = 0;
  uint64_t temp = bishops;
  while (temp) {
    temp = oneNoWest(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while (temp) {
    temp = oneNoEast(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while (temp) {
    temp = oneSoWest(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = bishops;
  while(temp) {
    temp = oneSoEast(temp);
    bishopMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  return bishopMoveBoard;
}

uint64_t rookMove(uint64_t rooks, uint64_t empty, uint64_t pieces) {
  uint64_t rookMoveBoard = 0;
  uint64_t temp = rooks;
  while (temp) {
    temp = oneNorth(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneSouth(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneWest(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  temp = rooks;
  while (temp) {
    temp = oneEast(temp);
    rookMoveBoard |= (temp & (empty | pieces));
    temp &= empty;
  }
  return rookMoveBoard;
}

uint64_t queenMove(uint64_t queen, uint64_t empty, uint64_t pieces) {
  return bishopMove(queen, empty, pieces) | rookMove(queen, empty, pieces);
}

uint64_t kingMove(uint64_t king, uint64_t empty, uint64_t pieces) {
  return (oneNoWest(king) | oneNorth(king) | oneNoEast(king) | oneEast(king) |
          oneSoEast(king) | oneSouth(king) | oneSoWest(king) | oneWest(king)) & 
           (empty | pieces);
}

bool areSquaresAttacked(const Board& b, color attacker, uint64_t attacked) {
  color defender = (attacker == white) ? black : white;
  uint64_t ownB = b.getBByColor(defender);
  uint64_t empty = b.getEmptySquares();
  
  if (attacker == white) {
    if (whitePawnAttack(b.getBByPieceAndColor(pawns, attacker), attacked) & attacked) return true;
  }
  else {
    if (blackPawnAttack(b.getBByPieceAndColor(pawns, attacker), attacked) & attacked) return true;
  }
  if (multKnightMove(b.getBByPieceAndColor(knights, attacker), empty, ownB) & attacked) return true;
  else if (bishopMove(b.getBByPieceAndColor(bishops, attacker), empty, ownB) & attacked) return true;
  else if (rookMove(b.getBByPieceAndColor(rooks, attacker), empty, ownB) & attacked) return true;
  else if (queenMove(b.getBByPieceAndColor(queens, attacker), empty, ownB) & attacked) return true;
  else if (kingMove(b.getBByPieceAndColor(kings, attacker), empty, ownB) & attacked) return true;
  return false;
}

bool isInCheck(const Board& b, color side) {
  color attacker = (side == white) ? black : white;
  return areSquaresAttacked(b, attacker, b.getBByPieceAndColor(kings, side));
}

void generatePawnBoards(std::vector<Move>& moves, std::vector<Move>& captures, std::vector<Move>& promotions, const Board& current) {
  uint64_t allPawns, individualPawn, onePushBoard, twoPushBoard, attackBoard, oneAttack, empty, ep, opposing;
  uint16_t from, to;
  color c = current.getTurn();
  color opponent = c == white ? black : white;

  allPawns = current.getBByPieceAndColor(pawns, current.getTurn());
  empty = current.getEmptySquares();
  ep = current.getBByPiece(enPassat);
  opposing = current.getBByColor(opponent);

  while (allPawns) {
    individualPawn = getLSB(allPawns);
    allPawns ^= individualPawn;

    from = bitBoardToPos(individualPawn);

    if (c == white) {
      onePushBoard = whitePawnPush(individualPawn, empty);
      twoPushBoard = whitePawnPushTwo(individualPawn, empty);
      attackBoard = whitePawnAttack(individualPawn, opposing | ep);
    }
    else {
      onePushBoard = blackPawnPush(individualPawn, empty);
      twoPushBoard = blackPawnPushTwo(individualPawn, empty);
      attackBoard = blackPawnAttack(individualPawn, opposing | ep);
    }

    if (onePushBoard) {
      to = bitBoardToPos(onePushBoard);
      if (onePushBoard & RANK_1 || onePushBoard & RANK_8) {
        promotions.push_back(Move(from, to, KN_PRMT));
        promotions.push_back(Move(from, to, B_PRMT));
        promotions.push_back(Move(from, to, R_PRMT));
        promotions.push_back(Move(from, to, Q_PRMT));
      }
      else {
        moves.push_back(Move(from, to, REGULAR));
      }
    }

    if (twoPushBoard) {
      to = bitBoardToPos(twoPushBoard);
      moves.push_back(Move(from, to, DOUBLE_PAWN));
    }

    while(attackBoard) {
      oneAttack = getLSB(attackBoard);
      attackBoard ^= oneAttack;
      to = bitBoardToPos(oneAttack);
      if (oneAttack & ep) {
        captures.push_back(Move(from, to, EP_CAPTURE));
      }
      else if ((oneAttack & RANK_1) || (oneAttack & RANK_8)) {
        promotions.push_back(Move(from, to, KN_PRMT_CAPT));
        promotions.push_back(Move(from, to, B_PRMT_CAPT));
        promotions.push_back(Move(from, to, R_PRMT_CAPT));
        promotions.push_back(Move(from, to, Q_PRMT_CAPT));
      }
      else {
        captures.push_back(Move(from, to, CAPTURE));
      }
    }
  }
  return;
}

void generatePieceBoards(std::vector<Move>& moves, std::vector<Move>& captures, const Board& current, piece p, std::function<uint64_t(uint64_t, uint64_t, uint64_t)> pieceMove) {
  uint64_t individualPiece, allPieces, individualMove, allMoves, empty, ep, opposingPieces;
  uint16_t from, to;
  color c = current.getTurn();
  color opponent = (c == white) ? black : white;

  allPieces = current.getBByPieceAndColor(p, c);
  
  empty = current.getEmptySquares();
  ep = current.getBByPiece(enPassat);
  opposingPieces = current.getBByColor(opponent);

  while (allPieces) {
    individualPiece = getLSB(allPieces);
    allPieces ^= individualPiece;

    allMoves = pieceMove(individualPiece, empty, opposingPieces | ep);
    
    from = bitBoardToPos(individualPiece);

    while (allMoves) {
      individualMove = getLSB(allMoves);
      allMoves ^= individualMove;

      to = bitBoardToPos(individualMove);

      if (individualMove & empty) {
        moves.push_back(Move(from, to, REGULAR));
      }
      else if (individualMove & ep) {
        captures.push_back(Move(from, to, EP_CAPTURE));
      }
      else {
        captures.push_back(Move(from, to, CAPTURE));
      }
    }
  }
  return;
}

void generateCastleBoards(std::vector<Move>& newMoves, const Board &current) {
  Board newBoard;
  uint16_t kingPos, qSidePos, kSidePos;
  color opponent, c;
  uint64_t rank;
  
  c = current.getTurn();
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

  if ((current.getBByPieceAndColor(castlingRights, c) & FILE_A) 
        && !(current.getAllPieces() & (Q_SIDE_BTWN_K_AND_R & rank))
        && !(areSquaresAttacked(current, opponent, Q_SIDE_VULN_SQUARES & rank))) {
    newMoves.push_back(Move(kingPos, qSidePos, Q_CASTLE));
  }
  if ((current.getBByPieceAndColor(castlingRights, c) & FILE_H) 
        && !(current.getAllPieces() & (K_SIDE_BTWN_K_AND_R & rank))
        && !(areSquaresAttacked(current, opponent, K_SIDE_VULN_SQUARES & rank))) {
    newMoves.push_back(Move(kingPos, qSidePos, K_CASTLE));
  }
  return;
}

void generateMoves(std::vector<Move>& newMoves, const Board &current) {
  color c = current.getTurn();
  
  std::vector<Move> moves, captures, promotions;

  if (current.getBByPieceAndColor(pawns, c) != 0) {
    generatePawnBoards(moves, captures, promotions, current);
  }
  if (current.getBByPieceAndColor(knights, c) != 0) {
    generatePieceBoards(moves, captures, current, knights, knightMove);
  }
  if (current.getBByPieceAndColor(rooks, c) != 0) {
    generatePieceBoards(moves, captures, current, rooks, rookMove);
  }
  if (current.getBByPieceAndColor(bishops, c) != 0) {
    generatePieceBoards(moves, captures, current, bishops, bishopMove);
  }
  if (current.getBByPieceAndColor(queens, c) != 0) {
    generatePieceBoards(moves, captures, current, queens, queenMove);
  }
  if (current.getBByPieceAndColor(kings, c) != 0) {
    generatePieceBoards(moves, captures, current, kings, kingMove);
  }
  if (current.getBByPieceAndColor(castlingRights, c) != 0) {
    generateCastleBoards(moves, current);
  }
  for (int i = 0; i < promotions.size(); ++i) {
    newMoves.push_back(promotions[i]);
  }
  for (int i = 0; i < captures.size(); ++i) {
    newMoves.push_back(captures[i]);
  }
  for (int i = 0; i < moves.size(); ++i) {
    newMoves.push_back(moves[i]);
  }
}