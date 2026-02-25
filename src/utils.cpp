#include <vector>
#include <random>

// Zobrist table: matriz para guardar valores aleatorios para cada posición y pieza
unsigned long long zobristTable[12][13];

// Inicializa la tabla de Zobrist con números aleatorios usando una semilla fija
void initZobrist() {
    std::mt19937_64 rng(12345); // Semilla fija para que el hash sea reproducible
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 13; j++) {
            zobristTable[i][j] = rng();
        }
    }
}

// Calcula el hash de un estado usando la tabla de Zobrist, considerando solo las piezas del patrón
unsigned long long computeHash(const std::vector<int>& state, const std::vector<int>& patternPieces) {
    unsigned long long h = 0;
    for(int i = 0; i < 12; i++) {
        bool isPattern = false;
        for(int p : patternPieces) {
            if(state[i] == p) {
                h ^= zobristTable[i][state[i]];
                isPattern = true;
                break;
            }
        }
        // Si la pieza no está en el patrón, se usa el valor del wildcard (0)
        if(!isPattern) {
            h ^= zobristTable[i][0];
        }
    }
    return h;
}