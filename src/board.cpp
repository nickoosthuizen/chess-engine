#include <cstdint>
#include <string>

#include "board.h"
#include "constants.h"
#include "utilFunctions.h"
#include <string>

Board::Board() {
  m_colors[white] = WHITE_START;
  m_colors[black] = BLACK_START;
  m_pieces[pawns] = PAWN_START;
  m_pieces[knights] = KNIGHT_START;
  m_pieces[rooks] = ROOK_START;
  m_pieces[bishops] = BISHOP_START;
  m_pieces[queens] = QUEEN_START;
  m_pieces[kings] = KING_START;
  m_pieces[enPassat] = 0;
  m_pieces[castlingRights] = ROOK_START;
  m_turn = white;
  m_halfClock = 0;
  m_fullCounter = 1;
}

Board::Board(std::string fen) {
  m_colors[white] = 0;
  m_colors[black] = 0;
  m_pieces[pawns] = 0;
  m_pieces[knights] = 0;
  m_pieces[rooks] = 0;
  m_pieces[bishops] = 0;
  m_pieces[queens] = 0;
  m_pieces[kings] = 0;
  m_pieces[enPassat] = 0;
  m_pieces[castlingRights] = 0;
  m_turn = white;
  m_halfClock = 0;
  m_fullCounter = 0;
  
  std::vector<std::string> fields, rows;
  split(fen, " ", fields);
  if (fields.size() != 6) return;
  split(fields[0], "/", rows);
  if (rows.size() != 8) return;

  int n = 63;
  for (int i = 0; i < rows.size(); ++i) {
    for (int j = 0; j < rows[i].size(); j++) {
      if (isupper(rows[i][j])) {
        m_colors[white] |= (1 << n);
      }
      else if (islower(rows[i][j])) {
        m_colors[black] |= (1 << n);
      }
      else if (isdigit(rows[i][j])) {
        n -= (rows[i][j] - '0');
        continue;
      }
      else {
        // if an incorrect character is found break out
        break;
      }

      switch (tolower(rows[i][j])) {
        case 'p':
          m_pieces[pawns] |= (1 << n);
          break;
        case 'n':
          m_pieces[knights] |= (1 << n);
          break;
        case 'r':
          m_pieces[rooks] |= (1 << n);
          break;
        case 'b': 
          m_pieces[bishops] |= (1 << n);
          break;
        case 'q':
          m_pieces[queens] |= (1 << n);
          break;
        case 'k':
          m_pieces[kings] |= (1 << n);
          break;
      }

      n -= 1;
    }
  }

  fields[1] == "w" ? m_turn = white : m_turn = black;

  for (int i = 0; i < fields[2].length(); ++i) {
    if (fields[2][i] == '-') {
      break;
    }

    switch (fields[2][i]) {
      case 'K':
        m_pieces[castlingRights] |= (WHITE_START & ROOK_START & FILE_H);
        break;
      case 'Q':
        m_pieces[castlingRights] |= (WHITE_START & ROOK_START & FILE_A);
        break;
      case 'k':
        m_pieces[castlingRights] |= (BLACK_START & ROOK_START & FILE_H);
        break;
      case 'q':
        m_pieces[castlingRights] |= (BLACK_START & ROOK_START & FILE_A);
        break;
    }
  }

  if (fields[3] == "-" || fields[3].length() < 2 || (fields[3][1] != '3' && fields[3][1] != '6')) m_pieces[enPassat] = 0;
  else m_pieces[enPassat] = squareToBit(fields[3]);


  (isWholeNumber(fields[4])) ? m_halfClock = std::stoi(fields[4], nullptr) : m_halfClock = 0;
  (isWholeNumber(fields[5])) ? m_fullCounter = std::stoi(fields[5], nullptr) : m_fullCounter = 1;
} 

bool Board::operator==(const Board& other) const {
  return (m_colors[white] == other.m_colors[white]) &&
         (m_colors[black] == other.m_colors[black]) &&
         (m_pieces[pawns] == other.m_pieces[pawns]) &&
         (m_pieces[knights] == other.m_pieces[knights]) &&
         (m_pieces[rooks] == other.m_pieces[rooks]) &&
         (m_pieces[bishops] == other.m_pieces[bishops]) &&
         (m_pieces[queens] == other.m_pieces[queens]) &&
         (m_pieces[kings] == other.m_pieces[kings]) &&
         (m_pieces[enPassat] == other.m_pieces[enPassat]) &&
         (m_pieces[castlingRights] == m_pieces[castlingRights]);
}

uint64_t Board::getAllPieces() const { return m_colors[white] | m_colors[black]; }
uint64_t Board::getEmptySquares() const { return ~(m_colors[white] | m_colors[black]); }
uint64_t Board::getBByPiece(piece p) const { return m_pieces[p]; }
uint64_t Board::getBByColor(color c) const { return m_colors[c]; }
uint64_t Board::getBByPieceAndColor(piece p, color c) const { return m_pieces[p] & m_colors[c]; }
color Board::getTurn() const { return m_turn; }
unsigned short Board::getHalfClock() const { return m_halfClock; }
unsigned short Board::getFullCounter() const { return m_fullCounter; }

void Board::setColor(uint64_t b, color c) { m_colors[c] = b; }
void Board::setPiece(uint64_t b, piece p) { m_pieces[p] = b; }
void Board::clear() {
  m_colors[white] = 0;
  m_colors[black] = 0;
  m_pieces[pawns] = 0;
  m_pieces[knights] = 0;
  m_pieces[rooks] = 0;
  m_pieces[bishops] = 0;
  m_pieces[queens] = 0;
  m_pieces[kings] = 0;
  m_pieces[enPassat] = 0;
  m_pieces[castlingRights] = 0;
}

int Board::makeMove(Move m) {
  uint16_t flag = m.getFlag();
  uint16_t from = m.getFrom();
  uint16_t to = m.getTo();
  uint64_t fromBoard = posToBitBoard(from);
  uint64_t toBoard = posToBitBoard(to);
  piece p = getPieceAt(fromBoard);

  if (p == notAPiece && flag != K_CASTLE && flag != Q_CASTLE) return -1;

  switch(flag) {
    case REGULAR:
      movePiece(fromBoard, toBoard, p);
      break;
    case DOUBLE_PAWN:
      movePiece(fromBoard, toBoard, p);
      m_turn == white ? m_pieces[enPassat] = fromBoard >> 8 : m_pieces[enPassat] = fromBoard << 8;
      break;
    case K_CASTLE:
      castle(false);
      break;
    case Q_CASTLE:
      castle(true);
      break;
    case CAPTURE:
      takePiece(fromBoard, toBoard, p);
      break;
    case EP_CAPTURE:
      takeEnPassat(fromBoard, toBoard, p);
      break;
    case KN_PRMT:
      promotePawn(fromBoard, knights);
      break;
    case B_PRMT:
      promotePawn(fromBoard, bishops);
      break;
    case R_PRMT:
      promotePawn(fromBoard, rooks);
      break;
    case Q_PRMT:
      promotePawn(fromBoard, queens);
      break;
    case KN_PRMT_CAPT:
      takePiece(fromBoard, toBoard, p);
      promotePawn(fromBoard, knights);
      break;
    case B_PRMT_CAPT:
      takePiece(fromBoard, toBoard, p);
      promotePawn(fromBoard, bishops);
      break;
    case R_PRMT_CAPT:
      takePiece(fromBoard, toBoard, p);
      promotePawn(fromBoard, rooks);
      break;
    case Q_PRMT_CAPT:
      takePiece(fromBoard, toBoard, p);
      promotePawn(fromBoard, queens);
      break;
    default:
      break;
  };

  prevMove = m;
}

/* 
 * If invalid moves position boards are given to the move functions, 
 * it will leave the board in an invalid state. Right now it is up to the 
 * caller to ensure corrent from and to are passed to save time 
 * on extra checks. 
 */

void Board::movePiece(uint64_t from, uint64_t to, piece p) {
  m_pieces[p] ^= from;
  m_pieces[p] |= to;
  m_colors[m_turn] ^= from;
  m_colors[m_turn] |= to;
  if (m_pieces[enPassat]) m_pieces[enPassat] = 0;
  if (m_turn == black) m_fullCounter++;
  if (p == rooks && (m_pieces[castlingRights] & from)) m_pieces[castlingRights] ^= from;
  if (p == kings && (m_pieces[castlingRights] & m_colors[m_turn])) m_pieces[castlingRights] ^= m_pieces[castlingRights];
  (p == pawns) ? m_halfClock = 0 : m_halfClock++;
  m_turn == white ? m_turn = black : m_turn = white;
}

void Board::takePiece(uint64_t from, uint64_t to, piece p) {
  m_colors[!m_turn] ^= to;
  for (int i = 0; i < 6; ++i) {
    if (to & m_pieces[i]) {
      m_pieces[i] ^= to;
    }
  }
  movePiece(from, to, p);
  m_halfClock = 0;
}

void Board::takeEnPassat(uint64_t from, uint64_t to, piece p) {
  uint64_t pawnPos = (m_turn == white) ? m_pieces[enPassat] >> 8 : m_pieces[enPassat] << 8;
  m_colors[!m_turn] ^= pawnPos;
  m_pieces[pawns] ^= pawnPos;
  movePiece(from, to, p);
  m_halfClock = 0;
}

void Board::promotePawn(uint64_t pos, piece newP) {
  m_pieces[pawns] ^= pos;
  m_pieces[newP] |= pos; 
}

void Board::castle(bool kq) {
  uint64_t colorStart, kingCastle, rookCastle, sideFile;
  colorStart = (m_turn == white) ? WHITE_START : BLACK_START;
  if (kq) {
    kingCastle = K_SIDE_KING_CASTLE;
    rookCastle = K_SIDE_ROOK_CASTLE;
    sideFile = FILE_H;
  }
  else {
    kingCastle = Q_SIDE_KING_CASTLE;
    rookCastle = Q_SIDE_ROOK_CASTLE;
    sideFile = FILE_A;
  }
  m_pieces[rooks] ^= colorStart & ROOK_START & sideFile;
  m_pieces[rooks] |= colorStart & rookCastle;
  m_pieces[kings] ^= colorStart & KING_START;
  m_pieces[kings] |= colorStart & kingCastle;
  m_colors[m_turn] ^= (colorStart & ((ROOK_START & sideFile) | KING_START));
  m_colors[m_turn] |= (colorStart & (rookCastle | kingCastle));
  if (m_pieces[enPassat]) m_pieces[enPassat] = 0;
  if (m_turn == black) m_fullCounter++;
  m_halfClock++;
  m_pieces[castlingRights] = m_pieces[castlingRights] & m_colors[!m_turn];
  m_turn == white ? m_turn = black : m_turn = white;
}

piece Board::getPieceAt(uint64_t pos) {
  if (pos & m_pieces[pawns]) return pawns;
  if (pos & m_pieces[knights]) return knights;
  if (pos & m_pieces[bishops]) return bishops;
  if (pos & m_pieces[rooks]) return rooks;
  if (pos & m_pieces[queens]) return queens;
  if (pos & m_pieces[kings]) return kings;
  return notAPiece;
}