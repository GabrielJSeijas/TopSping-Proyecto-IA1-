#include "solver.hpp"
#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

Solver::Solver(PDB& p1, PDB& p2) : pdb1(p1), pdb2(p2), nodesCount(0) {}

Solution Solver::solve(State startNode) {
    nodesCount = 0;
    int bound = heuristic(startNode); 
    std::vector<State> path;
    path.push_back(startNode);

    while (true) {
        int t = search(path, 0, bound); 
        if (t == -1) return {true, (int)path.size() - 1, nodesCount, path}; 
        if (t == 2147483647) return {false, 0, nodesCount, {}}; 
        bound = t; 
    }
}

int Solver::search(std::vector<State>& path, int g, int bound) {
    State current = path.back();
    nodesCount++;

    int f = g + heuristic(current);
    if (f > bound) return f;
    if (current.isGoal()) return -1;

    int min_val = 2147483647;

    // Probar las 3 acciones posibles
    for (int i = 0; i < 3; i++) {
        State next = current;
        if (i == 0) next.shiftLeft();
        else if (i == 1) next.shiftRight();
        else next.rotateK();

        // Evitar ciclos inmediatos
        if (path.size() > 1 && next.pieces == path[path.size() - 2].pieces) continue;

        path.push_back(next);
        int t = search(path, g + 1, bound);
        if (t == -1) return -1;
        if (t < min_val) min_val = t;
        path.pop_back();
    }
    return min_val;
}

int Solver::heuristic(const State& s) {
    unsigned long long h1 = computeHash(s.pieces, pdb1.pattern); 
    unsigned long long h2 = computeHash(s.pieces, pdb2.pattern);

    // Máximo de las PDBs para asegurar admisibilidad y consistencia
    return std::max(pdb1.getDistance(h1), pdb2.getDistance(h2)); 
}

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