#ifndef PDB_HPP
#define PDB_HPP

#include <vector>
#include <string>
#include <unordered_map>

class PDB {
public:
    std::unordered_map<unsigned long long, int> database;
    std::vector<int> pattern;

    PDB(std::vector<int> p);
    void generate();
    bool loadFromFile(std::string filename);
    void saveToFile(std::string filename);
    int getDistance(unsigned long long hash);
};

#endif