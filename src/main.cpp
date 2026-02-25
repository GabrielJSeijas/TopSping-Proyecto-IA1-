#include <iostream>
#include <vector>
#include <string>
#include "pdb.hpp"
#include "solver.hpp"
#include "utils.hpp"

// Validamos que se pasen los argumentos correctos: 12 números y el nombre del archivo de salida
int main(int argc, char* argv[]) {
    if (argc < 14) {
        std::cerr << "Uso: " << argv[0] << " <n1>...<n12> <archivo_salida>" << std::endl;
        return 1;
    }

    // Leemos el estado inicial del TopSpin desde los argumentos
    std::vector<int> start_pieces;
    for (int i = 1; i <= 12; ++i) {
        start_pieces.push_back(std::stoi(argv[i]));
    }
    std::string output_file = argv[13];

    // Inicializamos la tabla de hashing Zobrist para el manejo eficiente de estados
    initZobrist();

    // Definimos los patrones para las PDBs, usando grupos de 4 piezas como recomienda Bortoluzzi
    std::vector<int> pattern1 = {1, 2, 3, 4};
    std::vector<int> pattern2 = {9, 10, 11, 12};
    
    std::cout << "Inicializando Heuristica PDB..." << std::endl;
    PDB pdb1(pattern1);
    PDB pdb2(pattern2);

    // Intentamos cargar las PDBs desde archivo, si no existen las generamos
    if (!pdb1.loadFromFile("data/pdb1.bin")) pdb1.generate();
    if (!pdb2.loadFromFile("data/pdb2.bin")) pdb2.generate();

    // Creamos el estado inicial y el solver para ejecutar el algoritmo IDA*
    State initialState(start_pieces);
    Solver solver(pdb1, pdb2); 

    std::cout << "Buscando solucion..." << std::endl;
    Solution result = solver.solve(initialState);

    // Mostramos los resultados por pantalla y los guardamos en el archivo de salida
    if (result.found) {
        std::cout << "La solucion optima es: " << result.pathLength << std::endl;
        std::cout << "Total de nodos expandidos: " <<  result.nodesGenerated << std::endl;
        result.saveToFile(output_file);
    } else {
        std::cerr << "No se encontró solución." << std::endl;
        return 1;
    }

    return 0;
}
