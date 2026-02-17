#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "state.hpp"
#include "pdb.hpp"
#include <vector>
#include <string>

struct Solution {
    bool found;
    int pathLength;
    long long nodesGenerated;
    std::vector<State> path;

    void saveToFile(std::string filename);
};

class Solver {
private:
    PDB& pdb1;
    PDB& pdb2;
    long long nodesCount;

    int heuristic(const State& s);
    // IDA* Core
    int search(std::vector<State>& path, int g, int bound);

public:
    Solver(PDB& p1, PDB& p2);
    Solution solve(State startNode);
};

#endif