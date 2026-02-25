#include "pdb.hpp"
#include "utils.hpp"
#include "state.hpp"
#include <queue>
#include <unordered_map>
#include <fstream>
#include <vector>

// Constructor de la clase PDB, recibe el patrón a usar
PDB::PDB(std::vector<int> p) : pattern(p) {}

// Esta función genera la base de datos de patrones usando BFS
void PDB::generate() {
    State goal;
    // El estado meta es el orden natural de las piezas (1 al 12)
    for(int i = 1; i <= 12; i++) goal.pieces.push_back(i); 

    std::queue<std::pair<State, int>> q;
    q.push({goal, 0});
    
    unsigned long long goalHash = computeHash(goal.pieces, pattern);
    database[goalHash] = 0;

    while(!q.empty()) {
        auto [current, dist] = q.front();
        q.pop();

        // Se generan los vecinos aplicando las tres operaciones posibles
        std::vector<State> neighbors;
        
        State sLeft = current; sLeft.shiftLeft(); neighbors.push_back(sLeft);
        State sRight = current; sRight.shiftRight(); neighbors.push_back(sRight);
        State sRot = current; sRot.rotateK(); neighbors.push_back(sRot);

        for(auto& nextState : neighbors) {
            unsigned long long h = computeHash(nextState.pieces, pattern);
            // Si el estado no está en la base de datos, se agrega
            if(database.find(h) == database.end()) {
                database[h] = dist + 1;
                q.push({nextState, dist + 1});
            }
        }
    }
}

// Devuelve la distancia almacenada para un hash dado
int PDB::getDistance(unsigned long long hash) {
    if (database.count(hash)) return database[hash];
    return 0;
}

// Carga la base de datos desde un archivo binario
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

// Guarda la base de datos en un archivo binario
void PDB::saveToFile(std::string filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) return;
    for(auto const& [hash, dist] : database) {
        out.write((char*)&hash, sizeof(hash));
        out.write((char*)&dist, sizeof(dist));
    }
    out.close();
}