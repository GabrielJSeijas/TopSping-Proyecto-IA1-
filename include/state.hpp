#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
// Clase State: representa un estado del TopSpin, con un vector de piezas y el costo acumulado g(n).
struct State {
    std::vector<int> pieces;
    int g; // Costo acumulado

    State();
    State(std::vector<int> p);
    
    void shiftLeft();  // Mueve a la izquierda 
    void shiftRight(); // Mueve a la derecha 
    void rotateK();    // Invierte las primeras 4 piezas 
    bool isGoal();     // Verifica si es 1..12 
};

#endif