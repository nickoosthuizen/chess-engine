#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <cstdint>

void split(std::string toSplit, std::string delimiter, std::vector<std::string> &splitStrings);
uint64_t squareToBit(std::string square);
std::string bitToSquare(uint64_t bit);

#endif