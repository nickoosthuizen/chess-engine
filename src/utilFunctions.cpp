#include <vector>
#include <string>
#include <bitset>

#include "utilFunctions.h"
#include "constants.h"

void split(std::string toSplit, std::string delimiter, std::vector<std::string> &splitStrings) {
  size_t current, next;
  if (!splitStrings.empty()) splitStrings.clear();

  current = 0;
  next = toSplit.find(delimiter, current);

  while (next != std::string::npos) {
    splitStrings.push_back(toSplit.substr(current, next - current));
    current = next + delimiter.size();
    next = toSplit.find(delimiter, current);
  }

  if (current != toSplit.length()) splitStrings.push_back(toSplit.substr(current, toSplit.length() - current));
  return;
}

uint64_t squareToBit(std::string square) {
  if (square.length() != 2) return 0;
  uint64_t s = 0;
  switch(square[0]) {
    case 'a':
      s |= FILE_A;
      break;
    case 'b':
      s |= FILE_B;
      break;
    case 'c':
      s |= FILE_C;
      break;
    case 'd':
      s |= FILE_D;
      break;
    case 'e':
      s |= FILE_E;
      break;
    case 'f':
      s |= FILE_F;
      break;
    case 'g':
      s |= FILE_G;
      break;
    case 'h':
      s |= FILE_H;
      break;
  }
  switch (square[1]) {
    case '1':
      s &= RANK_1;
      break;
    case '2':
      s &= RANK_2;
      break;
    case '3':
      s &= RANK_3;
      break;
    case '4':
      s &= RANK_4;
      break;
    case '5':
      s &= RANK_5;
      break;
    case '6':
      s &= RANK_6;
      break;
    case '7':
      s &= RANK_7;
      break;
    case '8':
      s &= RANK_8;
      break;
  }
  return s;
}

uint16_t squareToPos(std::string square) {
  return bitBoardToPos(squareToBit(square));
}

std::string bitToSquare(uint64_t bit) {
  std::string square = "";
  if (bit & FILE_A) square += "a";
  else if (bit & FILE_B) square += "b";
  else if (bit & FILE_C) square += "c";
  else if (bit & FILE_D) square += "d";
  else if (bit & FILE_E) square += "e";
  else if (bit & FILE_F) square += "f";
  else if (bit & FILE_G) square += "g";
  else if (bit & FILE_H) square += "h";

  if (bit & RANK_1) square += "1";
  else if (bit & RANK_2) square += "2";
  else if (bit & RANK_3) square += "3";
  else if (bit & RANK_4) square += "4";
  else if (bit & RANK_5) square += "5";
  else if (bit & RANK_6) square += "6";
  else if (bit & RANK_7) square += "7";
  else if (bit & RANK_8) square += "8";

  return square;
}

std::string posToSquare(uint16_t pos) {
  return bitToSquare(posToBitBoard(pos));
}

bool isWholeNumber(const std:: string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) it++;
  return !s.empty() && it == s.end();
}

uint64_t posToBitBoard(uint16_t pos) { 
  uint64_t ret = 1;
  return (ret << pos); 
}

uint16_t bitBoardToPos(uint64_t b) {
  uint16_t pos = 0;
  if (b & FILE_A) pos += 7;
  else if (b & FILE_B) pos += 6;
  else if (b & FILE_C) pos += 5;
  else if (b & FILE_D) pos += 4;
  else if (b & FILE_E) pos += 3;
  else if (b & FILE_F) pos += 2;
  else if (b & FILE_G) pos += 1;

  if (b & RANK_2) pos += 8;
  else if (b & RANK_3) pos += 16;
  else if (b & RANK_4) pos += 24;
  else if (b & RANK_5) pos += 32;
  else if (b & RANK_6) pos += 40;
  else if (b & RANK_7) pos += 48;
  else if (b & RANK_8) pos += 56;

  return pos;
}

int populationCount(uint64_t n) {
  std::bitset<64> num (n);
  return num.count();
}

bool isValidFen(std::string fen) {
  std::vector<std::string> fields;
  std::vector<std::string> rows;
  int wKingPos, bKingPos;
  wKingPos = bKingPos = -1;

  split(fen, " ", fields);
  if (fields.size() < 4) return false;
  
  split(fields[0], "/", rows);
  if (rows.size() != 8) return false;

  int rowCounter;
  char c;
  for (int i = 0; i < 8; ++i) {
    rowCounter = 0;
    for (int j = 0; j < rows[i].size(); ++j) {
      c = tolower(rows[i][j]);
      if (c == 'p' || c == 'n' || c == 'b' || c == 'r' || c == 'q' || c == 'k') {
        if (rows[i][j] == 'k') bKingPos = i * 8 + rowCounter;
        else if (rows[i][j] == 'K') wKingPos = i * 8 + rowCounter; 
        rowCounter += 1;
      }
      else if (isdigit(c)) {
        rowCounter += (c - '0');
      }
      else {
        return false;
      }
    }
    if (rowCounter != 8) return false;
  }

  if (fields[1] != "w" && fields[1] != "b") return false;
  if (fields[2] != "-") {
    for (int i = 0; i < fields[2].size(); ++i) {
      if (fields[2][i] == 'Q') {
        if (wKingPos != 60) return false;
        if (rows[7][0] != 'R') return false;
      }
      else if (fields[2][i] == 'K') {
        if (wKingPos != 60) return false;
        if (rows[7][rows[7].length() - 1] != 'R') return false;
      }
      else if (fields[2][i] == 'q') {
        if (bKingPos != 4) return false;
        if (rows[0][0] != 'r') return false;
      }
      else if (fields[2][i] == 'k') {
        if (bKingPos != 4) return false;
        if (rows[0][rows[0].length() - 1] != 'r') return false;
      }
      else {
        return false;
      }
    }
  }

  if (fields[3] != "-" && !squareToBit(fields[3])) return false;

  if (4 < fields.size() && !isWholeNumber(fields[4])) return false;
  if (5 < fields.size() && !isWholeNumber(fields[5])) return false;

  return true;
}