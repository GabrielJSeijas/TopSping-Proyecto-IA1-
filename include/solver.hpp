#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "state.hpp"
#include "pdb.hpp"
#include <vector>
#include <string>

// Estructura para almacenar la solución encontrada por el algoritmo.
// Incluye si se encontró solución, la longitud del camino, el número de nodos generados y el camino como una secuencia de estados.
struct Solution {
    bool found; // Indica si se encontró una solución.
    int pathLength; // Longitud del camino desde el estado inicial hasta el objetivo.
    long long nodesGenerated; // Número total de nodos generados durante la búsqueda.
    std::vector<State> path; // Secuencia de estados que representa el camino solución.

    // Guarda la solución en un archivo especificado por filename.
    void saveToFile(std::string filename);
};

// Clase Solver: implementa el algoritmo de búsqueda (IDA*) usando dos PDBs para la heurística.
class Solver {
private:
    PDB& pdb1; // Referencia al primer Pattern Database (PDB) usado para calcular la heurística.
    PDB& pdb2; // Referencia al segundo PDB.
    long long nodesCount; // Contador de nodos generados durante la búsqueda.

    // Calcula la heurística para un estado dado usando los PDBs.
    int heuristic(const State& s);

    // Función principal de búsqueda recursiva para el algoritmo IDA*.
    // path: camino actual, g: costo acumulado, bound: límite de costo.
    int search(std::vector<State>& path, int g, int bound);

public:
    // Constructor: recibe referencias a los dos PDBs.
    Solver(PDB& p1, PDB& p2);

    // Ejecuta el algoritmo de búsqueda desde un estado inicial y retorna la solución.
    Solution solve(State startNode);
};

#endif