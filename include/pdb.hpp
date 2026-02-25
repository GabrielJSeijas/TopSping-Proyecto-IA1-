#ifndef PDB_HPP
#define PDB_HPP

#include <vector>
#include <string>
#include <unordered_map>


//Clase PDB (Pattern Database)

class PDB {
public:
    // Mapa que asocia un hash de la configuración con su distancia heurística
    std::unordered_map<unsigned long long, int> database;

    // Patrón utilizado para generar la base de datos
    std::vector<int> pattern;

    // Constructor: recibe el patrón que se va a utilizar
    PDB(std::vector<int> p);

    // Genera la base de datos de patrones a partir del patrón dado
    void generate();

    // Carga la base de datos desde un archivo
    bool loadFromFile(std::string filename);

    // Guarda la base de datos en un archivo
    void saveToFile(std::string filename);

    // Obtiene la distancia heurística asociada a un hash específico
    int getDistance(unsigned long long hash);
};

#endif