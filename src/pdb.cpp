#include "pdb.hpp"
#include "utils.hpp"
#include "state.hpp"
#include <queue>
#include <unordered_map>
#include <fstream>
#include <vector>

PDB::PDB(std::vector<int> p) : pattern(p) {}

void PDB::generate() {
    State goal;
    // El estado meta son los números del 1 al 12
    for(int i = 1; i <= 12; i++) goal.pieces.push_back(i); 

    std::queue<std::pair<State, int>> q;
    q.push({goal, 0});
    
    unsigned long long goalHash = computeHash(goal.pieces, pattern);
    database[goalHash] = 0;

    while(!q.empty()) {
        auto [current, dist] = q.front();
        q.pop();

        // Las acciones para retroceder desde la meta son las mismas
        std::vector<State> neighbors;
        
        State sLeft = current; sLeft.shiftLeft(); neighbors.push_back(sLeft);
        State sRight = current; sRight.shiftRight(); neighbors.push_back(sRight);
        State sRot = current; sRot.rotateK(); neighbors.push_back(sRot);

        for(auto& nextState : neighbors) {
            unsigned long long h = computeHash(nextState.pieces, pattern);
            if(database.find(h) == database.end()) {
                database[h] = dist + 1;
                q.push({nextState, dist + 1});
            }
        }
    }
}

int PDB::getDistance(unsigned long long hash) {
    if (database.count(hash)) return database[hash];
    return 0;
}

bool PDB::loadFromFile(std::string filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) return false;
    unsigned long long h;
    int d;
    while (in.read((char*)&h, sizeof(h)) && in.read((char*)&d, sizeof(d))) {
        database[h] = d;
    }
    in.close();
    return true;
}

void PDB::saveToFile(std::string filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) return;
    for(auto const& [hash, dist] : database) {
        out.write((char*)&hash, sizeof(hash));
        out.write((char*)&dist, sizeof(dist));
    }
    out.close();
}