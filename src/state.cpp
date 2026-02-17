#include "../include/state.hpp"
#include <vector>
#include <algorithm> 
// Constructores
State::State() : pieces(12, 0), g(0) {} 
State::State(std::vector<int> p) : pieces(p), g(0) {} 

// Acción: Mover a la izquierda - Mueve todas las piezas un lugar a la izquierda 
void State::shiftLeft() {
    std::rotate(pieces.begin(), pieces.begin() + 1, pieces.end()); 
}

// Acción: Mover a la derecha - Mueve todas las piezas un lugar a la derecha 
void State::shiftRight() {
    std::rotate(pieces.rbegin(), pieces.rbegin() + 1, pieces.rend());
}

// Acción: Rotar - Da la vuelta a las primeras cuatro piezas 
void State::rotateK() {
    std::reverse(pieces.begin(), pieces.begin() + 4); 
}

// Verifica si el estado es la meta (1 al 12 en orden) 
bool State::isGoal() {
    for(int i = 0; i < 12; i++) {
        if(pieces[i] != i + 1) return false; 
    }
    return true; 
}