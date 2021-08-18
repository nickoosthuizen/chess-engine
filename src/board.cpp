#include <cstdint>
#include <string>

#include "board.h"
#include "constants.h"
#include "utilFunctions.h"

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
  m_pieceCounts[white][pawns] = 8;
  m_pieceCounts[white][knights] = 2;
  m_pieceCounts[white][bishops] = 2;
  m_pieceCounts[white][rooks] = 2;
  m_pieceCounts[white][queens] = 1;
  m_pieceCounts[white][kings] = 1;
  m_pieceCounts[black][pawns] = 8;
  m_pieceCounts[black][knights] = 2;
  m_pieceCounts[black][bishops] = 2;
  m_pieceCounts[black][rooks] = 2;
  m_pieceCounts[black][queens] = 1;
  m_pieceCounts[black][kings] = 1;
  m_turn = white;
  m_halfClock = 0;
  m_fullCounter = 1;
  
}

/* 
 * Fen strings should be in the following format:
 * "position side-to-move castling-rights en-passat half-move-counter full-move-counter"
 * position: 8 lines separated by "/"s. 
 *           pieces are denoted by: king = "k", queen = "q", rook = "r", bishop = "b",
 *                                  knight = "n", pawn = "p"
 *           white pieces are uppercase, black pieces are lower case
 *           Empty squares are numeric digits representing the number of empty squares
 * side-to-move: white = "w", black = "b"
 * castling-rights: up to 4 characters: kingside = k, queenside = q
 *                  white pieces are uppercase, black pieces are lower case
 *                  if neither side can castle, "-" is instead placed here
 * en-passat: a two letter string of a lower case alphabetical character 
 *            followed by a numeric digit representing which square file 
 *            and rank is en passat. 
 *            if none, "-"
 * half-move-counter and full-move-counter: digits representing their values
 */
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
  m_pieceCounts[white][pawns] = 0;
  m_pieceCounts[white][knights] = 0;
  m_pieceCounts[white][bishops] = 0;
  m_pieceCounts[white][rooks] = 0;
  m_pieceCounts[white][queens] = 0;
  m_pieceCounts[white][kings] = 0;
  m_pieceCounts[black][pawns] = 0;
  m_pieceCounts[black][knights] = 0;
  m_pieceCounts[black][bishops] = 0;
  m_pieceCounts[black][rooks] = 0;
  m_pieceCounts[black][queens] = 0;
  m_pieceCounts[black][kings] = 0;
  m_turn = white;
  m_halfClock = 0;
  m_fullCounter = 0;
  

  std::vector<std::string> fields, rows;
  split(fen, " ", fields);
  if (fields.size() != 6) return;
  split(fields[0], "/", rows);
  if (rows.size() != 8) return;

  color current;

  int n = 63;
  for (int i = 0; i < rows.size(); ++i) {
    for (int j = 0; j < rows[i].size(); j++) {
      if (isupper(rows[i][j])) {
        m_colors[white] |= posToBitBoard(n);
        current = white;
      }
      else if (islower(rows[i][j])) {
        m_colors[black] |= posToBitBoard(n);
        current = black;
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
          m_pieces[pawns] |= posToBitBoard(n);
          m_pieceCounts[current][pawns]++;
          break;
        case 'n':
          m_pieces[knights] |= posToBitBoard(n);
          m_pieceCounts[current][knights]++;
          break;
        case 'r':
          m_pieces[rooks] |= posToBitBoard(n);
          m_pieceCounts[current][rooks]++;
          break;
        case 'b': 
          m_pieces[bishops] |= posToBitBoard(n);
          m_pieceCounts[current][bishops]++;
          break;
        case 'q':
          m_pieces[queens] |= posToBitBoard(n);
          m_pieceCounts[current][queens]++;
          break;
        case 'k':
          m_pieces[kings] |= posToBitBoard(n);
          m_pieceCounts[current][kings]++;
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


// Two boards are the same if their current state is the same, ignore previous move stack
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
         (m_pieces[castlingRights] == other.m_pieces[castlingRights]) && 
         (m_turn == other.m_turn) && 
         (m_halfClock == other.m_halfClock) && 
         (m_fullCounter == other.m_fullCounter);
}

uint64_t Board::getAllPieces() const { return m_colors[white] | m_colors[black]; }
uint64_t Board::getEmptySquares() const { return ~(m_colors[white] | m_colors[black]); }
uint64_t Board::getBByPiece(piece p) const { return m_pieces[p]; }
uint64_t Board::getBByColor(color c) const { return m_colors[c]; }
uint64_t Board::getBByPieceAndColor(piece p, color c) const { return m_pieces[p] & m_colors[c]; }
int Board::getPieceCount(piece p, color c) const { return m_pieceCounts[c][p]; }
color Board::getTurn() const { return m_turn; }
unsigned short Board::getHalfClock() const { return m_halfClock; }
unsigned short Board::getFullCounter() const { return m_fullCounter; }

void Board::makeMove(Move m) {
  uint16_t flag = m.getFlag();
  uint64_t fromBoard = posToBitBoard(m.getFrom());
  uint64_t toBoard = posToBitBoard(m.getTo());
  piece pToMove = getPieceAt(fromBoard);
  piece capturedPiece = notAPiece;

  if (pToMove == notAPiece) return;

  struct prevMoveInfo prev = {m, m_pieces[enPassat], m_pieces[castlingRights], notAPiece, m_halfClock};

  (pToMove == pawns) ? m_halfClock = 0 : m_halfClock++;

  switch(flag) {
    case REGULAR:
      movePiece(fromBoard, toBoard, pToMove);
      break;
    case DOUBLE_PAWN:
      movePiece(fromBoard, toBoard, pToMove);
      (m_turn == white) ? m_pieces[enPassat] = fromBoard << 8 : m_pieces[enPassat] = fromBoard >> 8;
      break;
    case K_CASTLE:
      castle(false);
      break;
    case Q_CASTLE:
      castle(true);
      break;
    case CAPTURE:
      capturedPiece = getPieceAt(toBoard);
      m_pieceCounts[!m_turn][capturedPiece]--;
      takePiece(fromBoard, toBoard, pToMove, capturedPiece);
      break;
    case EP_CAPTURE:
      capturedPiece = pawns;
      m_pieceCounts[!m_turn][capturedPiece]--;
      takeEnPassat(fromBoard, toBoard, pToMove);
      break;
    case KN_PRMT:
      movePiece(fromBoard, toBoard, pawns);
      promotePawn(toBoard, knights);
      break;
    case B_PRMT:
      movePiece(fromBoard, toBoard, pawns);
      promotePawn(toBoard, bishops);
      break;
    case R_PRMT:
      movePiece(fromBoard, toBoard, pawns);
      promotePawn(toBoard, rooks);
      break;
    case Q_PRMT:
      movePiece(fromBoard, toBoard, pawns);
      promotePawn(toBoard, queens);
      break;
    case KN_PRMT_CAPT:
      capturedPiece = getPieceAt(toBoard);
      m_pieceCounts[!m_turn][capturedPiece]--;
      takePiece(fromBoard, toBoard, pawns, capturedPiece);
      promotePawn(toBoard, knights);
      break;
    case B_PRMT_CAPT:
      capturedPiece = getPieceAt(toBoard);
      m_pieceCounts[!m_turn][capturedPiece]--;
      takePiece(fromBoard, toBoard, pawns, capturedPiece);
      promotePawn(toBoard, bishops);
      break;
    case R_PRMT_CAPT:
      capturedPiece = getPieceAt(toBoard);
      m_pieceCounts[!m_turn][capturedPiece]--;
      takePiece(fromBoard, toBoard, pawns, capturedPiece);
      promotePawn(toBoard, rooks);
      break;
    case Q_PRMT_CAPT:
      capturedPiece = getPieceAt(toBoard);
      m_pieceCounts[!m_turn][capturedPiece]--;
      takePiece(fromBoard, toBoard, pawns, capturedPiece);
      promotePawn(toBoard, queens);
      break;
    default:
      break;
  }

  prev.prevCaptured = capturedPiece;

  if (flag != DOUBLE_PAWN && m_pieces[enPassat]) m_pieces[enPassat] = 0;
  if (m_turn == black) m_fullCounter++;
  // moving a rook removes its right to castle
  if (pToMove == rooks && (m_pieces[castlingRights] & fromBoard)) m_pieces[castlingRights] ^= fromBoard;
  // moving a king removes color's right to castle
  if (pToMove == kings && (m_pieces[castlingRights] & m_colors[m_turn])) m_pieces[castlingRights] ^= (m_pieces[castlingRights] & m_colors[m_turn]);
  (m_turn == white) ? m_turn = black : m_turn = white;

  m_prevMoves.push(prev);
}

void Board::unMakeMove() {
  if (m_prevMoves.empty()) return;
  struct prevMoveInfo prev = m_prevMoves.top();
  m_prevMoves.pop(); 

  uint16_t flag = prev.prevMove.getFlag();
  uint64_t prevFromBoard = posToBitBoard(prev.prevMove.getFrom());
  uint64_t prevToBoard = posToBitBoard(prev.prevMove.getTo());
  piece pMoved = getPieceAt(prevToBoard);
  
  // reset the current turn
  color opponent = m_turn;
  m_turn = (m_turn == white) ? black : white;

  switch (flag) {
    // both regular pushes and double pawn pushes can be moved back
    case REGULAR:
    case DOUBLE_PAWN:
      movePiece(prevToBoard, prevFromBoard, pMoved);
      break;
    case K_CASTLE:
      undoCastle(false);
      break;
    case Q_CASTLE:
      undoCastle(true);
      break;
    case CAPTURE:
      m_pieceCounts[opponent][prev.prevCaptured]++;
      movePiece(prevToBoard, prevFromBoard, pMoved);
      undoCapture(prevToBoard, prev.prevCaptured, opponent);
      break;
    case EP_CAPTURE:
      {
        m_pieceCounts[opponent][prev.prevCaptured]++;
        movePiece(prevToBoard, prevFromBoard, pMoved);
        uint64_t pawnPos = (opponent == white) ? prevToBoard << 8 : prevToBoard >> 8;
        undoCapture(pawnPos, prev.prevCaptured, opponent);
      }
      break;
    case KN_PRMT:
      demotePawn(prevFromBoard, prevToBoard, knights);
      break;
    case B_PRMT:
      demotePawn(prevFromBoard, prevToBoard, bishops);
      break;
    case R_PRMT:
      demotePawn(prevFromBoard, prevToBoard, rooks);
      break;
    case Q_PRMT:
      demotePawn(prevFromBoard, prevToBoard, queens);
      break;
    case KN_PRMT_CAPT:
      m_pieceCounts[opponent][prev.prevCaptured]++;
      demotePawn(prevFromBoard, prevToBoard, knights);
      undoCapture(prevToBoard, prev.prevCaptured, opponent);
      break;
    case B_PRMT_CAPT:
      m_pieceCounts[opponent][prev.prevCaptured]++;
      demotePawn(prevFromBoard, prevToBoard, bishops);
      undoCapture(prevToBoard, prev.prevCaptured, opponent);
      break;
    case R_PRMT_CAPT:
      m_pieceCounts[opponent][prev.prevCaptured]++;
      demotePawn(prevFromBoard, prevToBoard, rooks);
      undoCapture(prevToBoard, prev.prevCaptured, opponent);
      break;
    case Q_PRMT_CAPT:
      m_pieceCounts[opponent][prev.prevCaptured]++;
      demotePawn(prevFromBoard, prevToBoard, queens);
      undoCapture(prevToBoard, prev.prevCaptured, opponent);
      break;
  }

  m_pieces[enPassat] = prev.prevEP;
  m_pieces[castlingRights] = prev.prevCastlingRights;
  m_halfClock = prev.prevHalfClock;
  if (m_turn == black) m_fullCounter--;
}

std::string Board::toFen() {
  uint64_t curBit;
  piece p;
  char curPiece;
  std::string fen = "";

  int n = 63;
  int emptyCounter = 0;
  for (n; 0 <= n; --n) {
    curBit = posToBitBoard(n);
    if (curBit & getEmptySquares()) {
      emptyCounter++;
    }
    else {
      if (0 < emptyCounter) {
        fen += std::to_string(emptyCounter);
        emptyCounter = 0;
      }
      p = getPieceAt(curBit);
      switch (p) {
        case pawns:
          curPiece = 'p';
          break;
        case knights:
          curPiece = 'n';
          break;
        case bishops:
          curPiece = 'b';
          break;
        case rooks:
          curPiece = 'r';
          break;
        case queens:
          curPiece = 'q';
          break;
        case kings:
          curPiece = 'k';
          break;
      }
      if (curBit & m_colors[white]) curPiece = toupper(curPiece);
      fen += curPiece;
    }

    if (n % 8 == 0) {
      if (0 < emptyCounter) {
        fen += std::to_string(emptyCounter);
        emptyCounter = 0;
      }
      if (n != 0) fen += '/';
    }
  }
  fen += ' ';

  m_turn == white ? fen += 'w' : fen += 'b';

  fen += ' ';

  if (m_pieces[castlingRights] & m_colors[white] & FILE_H) fen += 'K';
  if (m_pieces[castlingRights] & m_colors[white] & FILE_A) fen += 'Q';
  if (m_pieces[castlingRights] & m_colors[black] & FILE_H) fen += 'k';
  if (m_pieces[castlingRights] & m_colors[black] & FILE_A) fen += 'q';

  if (!m_pieces[castlingRights]) fen += '-';

  fen += ' ';

  if (m_pieces[enPassat]) fen += posToSquare(bitBoardToPos(m_pieces[enPassat]));
  else fen += '-';

  fen += ' ';

  fen += std::to_string(m_halfClock);

  fen += ' ';

  fen += std::to_string(m_fullCounter);

  return fen;
}

// ================ Private Functions ================

void Board::movePiece(uint64_t from, uint64_t to, piece p) {
  m_pieces[p] ^= from;
  m_pieces[p] |= to;
  m_colors[m_turn] ^= from;
  m_colors[m_turn] |= to;
}

void Board::takePiece(uint64_t from, uint64_t to, piece p, piece capturePiece) {
  m_colors[!m_turn] ^= to;
  m_pieces[capturePiece] ^= to;
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

/*
 *  qSide = true: queenside castle, 
 *        = false: kingside castle
 */ 
void Board::castle(bool qSide) {
  uint64_t colorStart, kingCastle, rookCastle, sideFile;
  colorStart = (m_turn == white) ? WHITE_START : BLACK_START;
  if (qSide) {
    kingCastle = Q_SIDE_KING_CASTLE;
    rookCastle = Q_SIDE_ROOK_CASTLE;
    sideFile = FILE_A;
  }
  else {
    kingCastle = K_SIDE_KING_CASTLE;
    rookCastle = K_SIDE_ROOK_CASTLE;
    sideFile = FILE_H;
  }
  m_pieces[rooks] ^= colorStart & ROOK_START & sideFile;
  m_pieces[rooks] |= colorStart & rookCastle;
  m_pieces[kings] ^= colorStart & KING_START;
  m_pieces[kings] |= colorStart & kingCastle;
  m_colors[m_turn] ^= (colorStart & ((ROOK_START & sideFile) | KING_START));
  m_colors[m_turn] |= (colorStart & (rookCastle | kingCastle));
  
  // remove the castling rights for the side that moved
  m_pieces[castlingRights] = m_pieces[castlingRights] & m_colors[!m_turn];
}

piece Board::getPieceAt(uint64_t pos) {
  if (pos & m_pieces[pawns]) return pawns;
  else if (pos & m_pieces[knights]) return knights;
  else if (pos & m_pieces[bishops]) return bishops;
  else if (pos & m_pieces[rooks]) return rooks;
  else if (pos & m_pieces[queens]) return queens;
  else if (pos & m_pieces[kings]) return kings;
  return notAPiece;
}

void Board::undoCapture(uint64_t pos, piece captured, color c) {
  m_colors[c] |= pos;
  m_pieces[captured] |= pos;
}

/*
 *  qSide = true: undo queenside castle, 
 *        = false: undo kingside castle
 */ 
void Board::undoCastle(bool qSide) {
  uint64_t colorStart, kingCastle, rookCastle, sideFile;
  colorStart = (m_turn == white) ? WHITE_START : BLACK_START;
  if (qSide) {
    kingCastle = Q_SIDE_KING_CASTLE;
    rookCastle = Q_SIDE_ROOK_CASTLE;
    sideFile = FILE_A;
  }
  else {
    kingCastle = K_SIDE_KING_CASTLE;
    rookCastle = K_SIDE_ROOK_CASTLE;
    sideFile = FILE_H;
  }
  m_pieces[rooks] ^= colorStart & rookCastle;
  m_pieces[rooks] |= colorStart & ROOK_START & sideFile;
  m_pieces[kings] ^= colorStart & kingCastle;
  m_pieces[kings] |= colorStart & KING_START;
  m_colors[m_turn] ^= colorStart & (rookCastle | kingCastle);
  m_colors[m_turn] |= colorStart & ((ROOK_START & sideFile) | KING_START);
}

void Board::demotePawn(uint64_t prevFrom, uint64_t prevTo, piece newP) {
  m_pieces[newP] ^= prevTo;
  m_pieces[pawns] ^= prevTo;
  movePiece(prevTo, prevFrom, pawns);
}