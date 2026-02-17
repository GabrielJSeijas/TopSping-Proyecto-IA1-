#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

struct State {
    std::vector<int> pieces;
    int g; // Costo acumulado

    State();
    State(std::vector<int> p);
    
    void shiftLeft();  // Mueve a la izquierda [cite: 571]
    void shiftRight(); // Mueve a la derecha [cite: 570]
    void rotateK();    // Invierte las primeras 4 piezas [cite: 572]
    bool isGoal();     // Verifica si es 1..12 [cite: 568]
};

#endif