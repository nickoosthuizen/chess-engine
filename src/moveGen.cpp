#include <vector>
#include <functional>

#include "moveGen.h"
#include "board.h"
#include "constants.h"

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
  return oneNoWest(king) | oneNorth(king) | oneNoEast(king) | oneEast(king) |
          oneSoEast(king) | oneSouth(king) | oneSoWest(king) | oneWest(king) & 
           (empty | pieces);
}

bool isInCheck(Board b, color c) {
  uint64_t kingB = b.getBByPieceAndColor(kings, c);
  uint64_t ownB = b.getBByColor(c);
  uint64_t empty = b.getEmptySquares();
  color opponent = (c == white) ? black : white;
  if (c == white) {
    if (blackPawnAttack(b.getBByPieceAndColor(pawns, black), ownB) & kingB) return true;
  }
  else {
    if (blackPawnAttack(b.getBByPieceAndColor(pawns, white), ownB) & kingB) return true;
  }
  if (knightMove(b.getBByPieceAndColor(knights, opponent), empty, ownB) & kingB) return true;
  if (bishopMove(b.getBByPieceAndColor(bishops, opponent), empty, ownB) & kingB) return true;
  if (rookMove(b.getBByPieceAndColor(rooks, opponent), empty, ownB) & kingB) return true;
  if (queenMove(b.getBByPieceAndColor(queens, opponent), empty, ownB), & kingB) return true;
  if (kingMove(b.getBByPieceAndColor(kings, opponent), empty, ownB) & kingB) return true;
  return false;  
}

void generatePawnBoards(std::vector<Board> &newBoards, Board current, color c) {
  std::vector<uint64_t> individualPawns, attackBoards;
  uint64_t onePushBoard, twoPushBoard;
  Board newBoard;

  isolateBits(individualPawns, current.getBByPieceAndColor(pawns, c));

  for (int i = 0; i < individualPawns.size(); i++) {
    attackBoards.clear();
    if (current.getTurn() == white) {
      onePushBoard = whitePawnPush(individualPawns[i], current.getEmptySquares());
      twoPushBoard = whitePawnPushTwo(individualPawns[i], current.getEmptySquares());
      isolateBits(attackBoards, whitePawnAttack(individualPawns[i], current.getBByColor(black) | current.getBByPiece(enPassat)));
    }
    else {
      onePushBoard = blackPawnPush(individualPawns[i], current.getEmptySquares());
      twoPushBoard = blackPawnPushTwo(individualPawns[i], current.getEmptySquares());
      isolateBits(attackBoards, whitePawnAttack(individualPawns[i], current.getBByColor(white) | current.getBByPiece(enPassat)));
    }
    if (onePushBoard) {
      newBoard = current;
      newBoard.movePiece(individualPawns[i], onePushBoard, pawns);
      if (onePushBoard & RANK_1 || onePushBoard & RANK_8) {
        generatePromotionBoards(newBoards, newBoard, c);
      }
      else {
        newBoards.push_back(newBoard);
      }
    }
    if (twoPushBoard) {
      newBoard = current;
      newBoard.movePiece(individualPawns[i], twoPushBoard, pawns);
      // If a pawn can move two squares, it could have moved one and is now 
      // enpassat
      newBoard.setPiece(onePushBoard, enPassat);
      newBoards.push_back(newBoard);
    }
    for (int j = 0; j < attackBoards.size(); j++) {
      newBoard = current;
      if (attackBoards[i] & current.getBByPiece(enPassat)) {
        newBoard.takeEnPassat(individualPawns[i], attackBoards[j], pawns);
      }
      else {
        newBoard.takePiece(individualPawns[i], attackBoards[j], pawns);
      }
      if (attackBoards[i] & RANK_1 || attackBoards[i] & RANK_8) {
        generatePromotionBoards(newBoards, newBoard);
      }
      else {
        newBoards.push_back(newBoard);
      }
    }
  }
  return;
}

// Note: has extra logic for handling castling rights, see about removing it
void generatePieceBoards(std::vector<Board> &newBoards, Board current, piece p, std::function<uint64_t(uint64_t, uint64_t, uint64_t)> pieceMove) {
  std::vector<uint64_t> individualPieces, moves;
  uint64_t moveBoard;
  Board newBoard, baseBoard;
  color c = current.getTurn();

  color opponent = (c == white) ? black : white;

  // moving the king removes the right to castle
  if (p == kings && current.getBByPieceAndColor(castlingRights, c)) {
    current.setPiece(current.getBByPieceAndColor(castlingRights, opponent), castlingRights);
  }

  isolateBits(individualPieces, current.getBByPieceAndColor(p, c));

  for (int i = 0; i < individualPieces.size(); i++) {
    moveBoard = pieceMove(individualPieces[i], current.getEmptySquares(), current.getBByColor(opponent) | current.getBByPiece(enPassat));
    isolateBits(moves, moveBoard);
    baseBoard = current;

    // remove a moved rook from the castling rights
    if (p == rooks && (current.getBByPieceAndColor(castlingRights, c) & individualPieces[i])) {
      baseBoard.setPiece(current.getBByPiece(castlingRights) ^ individualPieces[i], castlingRights);
    }

    for (int j = 0; j < moves.size(); j++) {
      newBoard = baseBoard;
      if (moves[j] & baseBoard.getEmptySquares()) {
        newBoard.movePiece(individualPieces[i], moves[j], p);
      }
      else if (moves[j] & baseBoard.getBByPiece(enPassat)) {
        newBoard.takeEnPassat(individualPieces[i], moves[j], p);
      }
      else {
        newBoard.takePiece(individualPieces[i], moves[j], p);
      }
      newBoards.push_back(newBoard);
    }
  }
  return;
}

void generateCastleBoards(std::vector<Board> &newBoards, Board current) {
  Board newBoard;
  color c = current.getTurn();
  if ((current.getBByPieceAndColor(castlingRights, c) & FILE_A) && (current.getEmptySquares() & Q_SIDE_BTWN_K_AND_R)) {
    newBoard = current;
    newBoard.castle(false);
  }
  if ((current.getBByPieceAndColor(castlingRights, c) & FILE_H) && (current.getEmptySquares() & K_SIDE_BTWN_K_AND_R)) {
    newBoard = current;
    newBoard.castle(true);
  }
  return;
}

void generatePromotionBoards(std::vector<Board> &newBoards, Board current, color c) {
  uint64_t pawnB = current.getBByPieceAndColor(pawns, c);
  pawnB = (c == white) ? pawnB & FILE_H : pawnB & FILE_A;
  if (!pawnB) return;
  Board newBoard = current;
  newBoard.promotePawn(pawnB, knights);
  newBoards.push_back(newBoard);
  newBoard = current;
  newBoard.promotePawn(pawnB, bishops);
  newBoards.push_back(newBoard);
  newBoard = current;
  newBoard.promotePawn(pawnB, rooks);
  newBoards.push_back(newBoard);
  newBoard = current;
  newBoard.promotePawn(pawnB, queens);
  newBoards.push_back(newBoard);
}

void generateMoves(std::vector<Board> &newBoards, Board current) {
  std::vector<Board> potentialBoards;
  color c = current.getTurn();
  if (0 < newBoards.size()) {
    newBoards.clear();
  }
  if (current.getBByPieceAndColor(pawns, c) != 0) {
    generatePawnBoards(potentialBoards, current);
  }
  if (current.getBByPieceAndColor(knights, c) != 0) {
    generatePieceBoards(potentialBoards, current, knights, knightMove);
  }
  if (current.getBByPieceAndColor(rooks, c) != 0) {

    generatePieceBoards(potentialBoards, current, rooks, rookMove);
  }
  if (current.getBByPieceAndColor(bishops, c) != 0) {
    generatePieceBoards(potentialBoards, current, bishops, bishopMove);
  }
  if (current.getBByPieceAndColor(queens, c) != 0) {
    generatePieceBoards(potentialBoards, current, queens, queenMove);
  }
  if (current.getBByPieceAndColor(kings, c) != 0) {
    generatePieceBoards(potentialBoards, current, kings, kingMove);
  }
  if (current.getBByPieceAndColor(castlingRights, c) != 0) {
    generateCastleBoards(potentialBoards, current);
  }
  for (int i = 0; i < potentialBoards.size(); i++) {
    if (!isInCheck(potentialBoards[i], c)) {
      newBoards.push_back(potentialBoards[i]);
    }
  }
}