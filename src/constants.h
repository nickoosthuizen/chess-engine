#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <climits>

// Board initialization constants
const uint64_t WHITE_START = 0x000000000000FFFF;
const uint64_t BLACK_START = 0xFFFF000000000000;
const uint64_t PAWN_START = 0x00FF00000000FF00;
const uint64_t KNIGHT_START = 0x4200000000000042;
const uint64_t ROOK_START = 0x8100000000000081;
const uint64_t BISHOP_START = 0x2400000000000024;
const uint64_t QUEEN_START = 0x1000000000000010;
const uint64_t KING_START = 0x0800000000000008;

// castling constants
const uint64_t Q_SIDE_BTWN_K_AND_R = 0x7000000000000070;
const uint64_t K_SIDE_BTWN_K_AND_R = 0x0600000000000006;
const uint64_t Q_SIDE_VULN_SQUARES = 0x3800000000000038;
const uint64_t K_SIDE_VULN_SQUARES = 0x0E0000000000000E;

const uint64_t Q_SIDE_KING_CASTLE = 0x2000000000000020;
const uint64_t Q_SIDE_ROOK_CASTLE = 0x1000000000000010;
const uint64_t K_SIDE_KING_CASTLE = 0x0200000000000002;
const uint64_t K_SIDE_ROOK_CASTLE = 0x0400000000000004;

// File and rank constants
const uint64_t FILE_A = 0x8080808080808080;
const uint64_t FILE_B = 0x4040404040404040;
const uint64_t FILE_C = 0x2020202020202020;
const uint64_t FILE_D = 0x1010101010101010;
const uint64_t FILE_E = 0x0808080808080808;
const uint64_t FILE_F = 0x0404040404040404;
const uint64_t FILE_G = 0x0202020202020202;
const uint64_t FILE_H = 0x0101010101010101;

const uint64_t NOT_FILE_A = 0x7F7F7F7F7F7F7F7F;
const uint64_t NOT_FILE_H = 0xFEFEFEFEFEFEFEFE;

const uint64_t RANK_1 = 0x00000000000000FF;
const uint64_t RANK_2 = 0x000000000000FF00;
const uint64_t RANK_3 = 0x0000000000FF0000;
const uint64_t RANK_4 = 0x00000000FF000000;
const uint64_t RANK_5 = 0x000000FF00000000;
const uint64_t RANK_6 = 0x0000FF0000000000;
const uint64_t RANK_7 = 0x00FF000000000000;
const uint64_t RANK_8 = 0xFF00000000000000;

// Move Type flags
const uint16_t REGULAR = 0x00;
const uint16_t DOUBLE_PAWN = 0x01;
const uint16_t K_CASTLE = 0x02;
const uint16_t Q_CASTLE = 0x03;
const uint16_t CAPTURE = 0x04;
const uint16_t EP_CAPTURE = 0x05;
const uint16_t KN_PRMT = 0x06;
const uint16_t B_PRMT = 0x07;
const uint16_t R_PRMT = 0x08;
const uint16_t Q_PRMT = 0x09;
const uint16_t KN_PRMT_CAPT = 0x0A;
const uint16_t B_PRMT_CAPT = 0x0B;
const uint16_t R_PRMT_CAPT = 0x0C;
const uint16_t Q_PRMT_CAPT = 0x0D;

//Piece scores
const int PAWN_VAL = 1;
const int KNIGHT_VAL = 3;
const int BISHOP_VAL = 3;
const int ROOK_VAL = 5;
const int QUEEN_VAL = 9;
const int CHECK_MATE_WIN = INT_MAX;
// CHECK_MATE_LOSE is INT_MIN + 1 to be able to select an initial move
// even if it means a loss
const int CHECK_MATE_LOSE = INT_MIN + 1;
const int DRAW_VAL = 0;

#endif