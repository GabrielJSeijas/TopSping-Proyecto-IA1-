#include <iostream>
#include <vector>
#include <string>
#include "pdb.hpp"    // Debes mover tus clases a headers
#include "solver.hpp" // Para la lógica de IDA*
#include "utils.hpp"  // Para initZobrist()

int main(int argc, char* argv[]) {
    // 1. Validación de argumentos (12 números + 1 nombre de archivo)
    if (argc < 14) {
        std::cerr << "Uso: " << argv[0] << " <n1>...<n12> <archivo_salida>" << std::endl;
        return 1;
    }

    // 2. Leer estado inicial desde los argumentos
    std::vector<int> start_pieces;
    for (int i = 1; i <= 12; ++i) {
        start_pieces.push_back(std::stoi(argv[i]));
    }
    std::string output_file = argv[13];

    // 3. Inicializar Tablas de Hashing (Zobrist)
    initZobrist();

    // 4. Configurar las PDBs (Selección de patrones)
    // Usamos patrones de tamaño 4 como sugiere Bortoluzzi para balancear tiempo
    std::vector<int> pattern1 = {1, 2, 3, 4};
    std::vector<int> pattern2 = {9, 10, 11, 12};
    
    std::cout << "Inicializando Heuristica PDB..." << std::endl;
    PDB pdb1(pattern1);
    PDB pdb2(pattern2);

    // Intentar cargar desde archivo para ahorrar tiempo, si no, generar
    if (!pdb1.loadFromFile("data/pdb1.bin")) pdb1.generate();
    if (!pdb2.loadFromFile("data/pdb2.bin")) pdb2.generate();

    // 5. Ejecutar el Agente de Búsqueda IDA*
    State initialState(start_pieces);
    Solver solver(pdb1, pdb2); 

    std::cout << "Buscando solucion para TopSpin (12 piezas)..." << std::endl;
    Solution result = solver.solve(initialState);

    // 6. Salida de resultados según el proyecto
    if (result.found) {
        // Por salida estándar
        std::cout << result.pathLength << std::endl;
        std::cout << result.nodesGenerated << std::endl;

        // Al archivo de salida
        result.saveToFile(output_file);
    } else {
        std::cerr << "No se encontró solución." << std::endl;
        return 1;
    }

    return 0;
}