#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

void initZobrist();
unsigned long long computeHash(const std::vector<int>& state, const std::vector<int>& patternPieces);

#endif