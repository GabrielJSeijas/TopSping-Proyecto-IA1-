#include "../include/state.hpp"
#include <vector>
#include <algorithm>

// Constructor por defecto: inicializa el vector de piezas en cero y g en cero
State::State() : pieces(12, 0), g(0) {}

// Constructor que recibe un vector de piezas, inicializa g en cero
State::State(std::vector<int> p) : pieces(p), g(0) {}

// Mueve todas las piezas una posición a la izquierda
void State::shiftLeft() {
    std::rotate(pieces.begin(), pieces.begin() + 1, pieces.end());
}

// Mueve todas las piezas una posición a la derecha
void State::shiftRight() {
    std::rotate(pieces.rbegin(), pieces.rbegin() + 1, pieces.rend());
}

// Invierte las primeras cuatro piezas del vector
void State::rotateK() {
    std::reverse(pieces.begin(), pieces.begin() + 4);
}

// Verifica si el estado actual es el objetivo (piezas ordenadas del 1 al 12)
bool State::isGoal() {
    for(int i = 0; i < 12; i++) {
        if(pieces[i] != i + 1) return false;
    }
    return true;
}