#include <vector>
#include <random>

// Tabla de Zobrist: 12 posiciones x 13 posibles valores (1-12 y 0 para wildcard)
unsigned long long zobristTable[12][13];

void initZobrist() {
    std::mt19937_64 rng(12345); // Semilla fija para que siempre de el mismo hash
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 13; j++) {
            zobristTable[i][j] = rng();
        }
    }
}

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
        if(!isPattern) {
            h ^= zobristTable[i][0]; // 0 representa el wildcard (pieza no interesante)
        }
    }
    return h;
}