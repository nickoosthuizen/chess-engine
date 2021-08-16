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
uint64_t oneNorth(uint64_t b) { return b << 8; }
uint64_t oneSouth(uint64_t b) { return b >> 8; }
uint64_t oneEast(uint64_t b) { return (b & NOT_FILE_H) >> 1; }
uint64_t oneWest(uint64_t b) { return (b & NOT_FILE_A) << 1; }
uint64_t oneNoEast(uint64_t b) { return (b & NOT_FILE_H) << 7; }
uint64_t oneNoWest(uint64_t b) { return (b & NOT_FILE_A) << 9; }
uint64_t oneSoEast(uint64_t b) { return (b & NOT_FILE_H) >> 9; }
uint64_t oneSoWest(uint64_t b) { return (b & NOT_FILE_A) >> 7; }

void isolateBits(std::vector<uint64_t> &boards, uint64_t b) {
  if (0 < boards.size()) {
    boards.clear();
  }
  // Isolate the least significant bit set to 1 and push it to boards
  uint64_t lsb;
  while (b) {
    lsb = b & -b;
    boards.push_back(lsb);
    b ^= lsb;
  }
  return;
}

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
  uint64_t newKnights = 0;
  uint64_t temp = 0;
  temp = oneNoWest(knights);
  newKnights = newKnights | oneWest(temp) | oneNorth(temp);
  temp = oneNoEast(knights);
  newKnights = newKnights | oneEast(temp) | oneNorth(temp);
  temp = oneSoWest(knights);
  newKnights = newKnights | oneWest(temp) | oneSouth(temp);
  temp = oneSoEast(knights);
  newKnights = (newKnights | oneEast(temp) | oneSouth(temp)) & (empty | pieces);
  return newKnights;
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
  if (knightMove(b.getBByPieceAndColor(knights, attacker), empty, ownB) & attacked) return true;
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

void generatePawnBoards(std::vector<Move>& newMoves, const Board& current) {
  std::vector<uint64_t> individualPawns, attackBoards;
  uint64_t onePushBoard, twoPushBoard;
  uint16_t from, to;

  isolateBits(individualPawns, current.getBByPieceAndColor(pawns, current.getTurn()));

  for (int i = 0; i < individualPawns.size(); ++i) {
    from = bitBoardToPos(individualPawns[i]);
    attackBoards.clear();

    if (current.getTurn() == white) {
      onePushBoard = whitePawnPush(individualPawns[i], current.getEmptySquares());
      twoPushBoard = whitePawnPushTwo(individualPawns[i], current.getEmptySquares());
      isolateBits(attackBoards, whitePawnAttack(individualPawns[i], current.getBByColor(black) | current.getBByPiece(enPassat)));
    }
    else {
      onePushBoard = blackPawnPush(individualPawns[i], current.getEmptySquares());
      twoPushBoard = blackPawnPushTwo(individualPawns[i], current.getEmptySquares());
      isolateBits(attackBoards, blackPawnAttack(individualPawns[i], current.getBByColor(white) | current.getBByPiece(enPassat)));
    }

    if (onePushBoard) {
      to = bitBoardToPos(onePushBoard);
      if (onePushBoard & RANK_1 || onePushBoard & RANK_8) {
        newMoves.push_back(Move(from, to, KN_PRMT));
        newMoves.push_back(Move(from, to, B_PRMT));
        newMoves.push_back(Move(from, to, R_PRMT));
        newMoves.push_back(Move(from, to, Q_PRMT));
      }
      else {
        newMoves.push_back(Move(from, to, REGULAR));
      }
    }

    if (twoPushBoard) {
      to = bitBoardToPos(twoPushBoard);
      newMoves.push_back(Move(from, to, DOUBLE_PAWN));
    }

    for (int j = 0; j < attackBoards.size(); j++) {
      to = bitBoardToPos(attackBoards[j]);
      if (attackBoards[j] & current.getBByPiece(enPassat)) {
        newMoves.push_back(Move(from, to, EP_CAPTURE));
      }
      else if ((attackBoards[j] & RANK_1) || (attackBoards[j] & RANK_8)) {
        newMoves.push_back(Move(from, to, KN_PRMT_CAPT));
        newMoves.push_back(Move(from, to, B_PRMT_CAPT));
        newMoves.push_back(Move(from, to, R_PRMT_CAPT));
        newMoves.push_back(Move(from, to, Q_PRMT_CAPT));
      }
      else {
        newMoves.push_back(Move(from, to, CAPTURE));
      }
    }
  }
  return;
}

void generatePieceBoards(std::vector<Move>& newMoves, const Board& current, piece p, std::function<uint64_t(uint64_t, uint64_t, uint64_t)> pieceMove) {
  std::vector<uint64_t> individualPieces, moves;
  uint64_t moveBoard;
  uint16_t from, to;
  color c = current.getTurn();
  color opponent = (c == white) ? black : white;

  isolateBits(individualPieces, current.getBByPieceAndColor(p, c));

  for (int i = 0; i < individualPieces.size(); ++i) {
    moveBoard = pieceMove(individualPieces[i], current.getEmptySquares(), current.getBByColor(opponent) | current.getBByPiece(enPassat));
    isolateBits(moves, moveBoard);
    
    from = bitBoardToPos(individualPieces[i]);

    for (int j = 0; j < moves.size(); j++) {
      to = bitBoardToPos(moves[j]);
      if (moves[j] & current.getEmptySquares()) {
        newMoves.push_back(Move(from, to, REGULAR));
      }
      else if (moves[j] & current.getBByPiece(enPassat)) {
        newMoves.push_back(Move(from, to, EP_CAPTURE));
      }
      else {
        newMoves.push_back(Move(from, to, CAPTURE));
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
  if (0 < newMoves.size()) {
    newMoves.clear();
  }
  if (current.getBByPieceAndColor(pawns, c) != 0) {
    generatePawnBoards(newMoves, current);
  }
  if (current.getBByPieceAndColor(knights, c) != 0) {
    generatePieceBoards(newMoves, current, knights, knightMove);
  }
  if (current.getBByPieceAndColor(rooks, c) != 0) {
    generatePieceBoards(newMoves, current, rooks, rookMove);
  }
  if (current.getBByPieceAndColor(bishops, c) != 0) {
    generatePieceBoards(newMoves, current, bishops, bishopMove);
  }
  if (current.getBByPieceAndColor(queens, c) != 0) {
    generatePieceBoards(newMoves, current, queens, queenMove);
  }
  if (current.getBByPieceAndColor(kings, c) != 0) {
    generatePieceBoards(newMoves, current, kings, kingMove);
  }
  if (current.getBByPieceAndColor(castlingRights, c) != 0) {
    generateCastleBoards(newMoves, current);
  }
}