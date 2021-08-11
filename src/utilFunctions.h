#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <string>
#include <vector>
#include <cstdint>

#include "Board.h"

void split(std::string toSplit, std::string delimiter, std::vector<std::string> &splitStrings);
uint64_t squareToBit(std::string square);
std::string bitToSquare(uint64_t bit);
bool isWholeNumber(const std:: string& s);
int populationCount(uint64_t n);

#endif