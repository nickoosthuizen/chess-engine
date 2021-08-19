#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <string>
#include <vector>
#include <cstdint>
#include <string.h> // ffsll

void split(std::string toSplit, std::string delimiter, std::vector<std::string> &splitStrings);
uint64_t squareToBit(std::string square);
uint16_t squareToPos(std::string square);
std::string bitToSquare(uint64_t bit);
std::string posToSquare(uint16_t pos);
bool isWholeNumber(const std:: string& s);

inline uint64_t posToBitBoard(uint16_t pos) { return 1ULL << pos; }
inline uint16_t bitBoardToPos(uint64_t b) { return ffsll(b) - 1; }

bool isValidFen(std::string fen); 

#endif