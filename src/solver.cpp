#include "solver.hpp"
#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// Constructor de la clase Solver, inicializa las PDBs y el contador de nodos
Solver::Solver(PDB& p1, PDB& p2) : pdb1(p1), pdb2(p2), nodesCount(0) {}

// Método principal para resolver el problema usando IDA*
Solution Solver::solve(State startNode) {
    nodesCount = 0;
    int bound = heuristic(startNode); // Inicializa el límite con el valor heurístico del estado inicial
    std::vector<State> path;
    path.push_back(startNode);

    while (true) {
        int t = search(path, 0, bound); // Realiza la búsqueda recursiva
        if (t == -1) return {true, (int)path.size() - 1, nodesCount, path}; // Solución encontrada
        if (t == 2147483647) return {false, 0, nodesCount, {}}; // No hay solución
        bound = t; // Actualiza el límite para la siguiente iteración
    }
}

// Búsqueda recursiva para IDA*
int Solver::search(std::vector<State>& path, int g, int bound) {
    State current = path.back();
    nodesCount++;

    int f = g + heuristic(current); // Calcula el valor f(n) = g(n) + h(n)
    if (f > bound) return f; // Si se pasa del límite, retorna el nuevo límite
    if (current.isGoal()) return -1; // Si es el estado meta, retorna -1 para indicar éxito

    int min_val = 2147483647;

    // Se prueban las tres acciones posibles: shiftLeft, shiftRight y rotateK
    for (int i = 0; i < 3; i++) {
        State next = current;
        if (i == 0) next.shiftLeft();
        else if (i == 1) next.shiftRight();
        else next.rotateK();

        // Evita ciclos inmediatos comparando con el estado anterior
        if (path.size() > 1 && next.pieces == path[path.size() - 2].pieces) continue;

        path.push_back(next);
        int t = search(path, g + 1, bound);
        if (t == -1) return -1; // Si se encuentra solución, retorna -1
        if (t < min_val) min_val = t; // Guarda el menor valor de f
        path.pop_back();
    }
    return min_val;
}

// Calcula la heurística usando las dos PDBs
int Solver::heuristic(const State& s) {
    unsigned long long h1 = computeHash(s.pieces, pdb1.pattern); 
    unsigned long long h2 = computeHash(s.pieces, pdb2.pattern);

    // Se toma el máximo de las dos heurísticas para mantener la admisibilidad
    return std::max(pdb1.getDistance(h1), pdb2.getDistance(h2)); 
}

// Guarda la solución encontrada en un archivo
void Solution::saveToFile(std::string filename) {
    std::ofstream out(filename);
    if (!out.is_open()) return;

    for (const auto& s : path) {
        for (int i = 0; i < 12; i++) {
            out << s.pieces[i] << (i == 11 ? "" : " "); 
        }
        out << "\n"; 
    }
    out.close();
}