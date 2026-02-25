#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

// Inicializa los valores de Zobrist hashing.
// Esta función debe ser llamada antes de usar computeHash para asegurar que los valores aleatorios estén listos.
void initZobrist();

// Calcula el hash de un estado dado usando Zobrist hashing.
// state: vector que representa el estado actual del juego.
// patternPieces: vector que contiene las piezas relevantes para el patrón.
// Retorna un valor hash único para el estado y patrón dados.
unsigned long long computeHash(const std::vector<int>& state, const std::vector<int>& patternPieces);

#endif