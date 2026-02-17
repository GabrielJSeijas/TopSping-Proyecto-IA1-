Agente de Búsqueda para el Rompecabezas TopSpin (12 piezas)
Realizado por 
Angel Valero 18-10436
Gabriel Seijas 19-00036

Este proyecto implementa un agente inteligente capaz de resolver el puzzle TopSpin de 12 piezas de forma óptima. Utiliza el algoritmo de búsqueda informada IDA* (Iterative Deepening A*) y una heurística basada en Pattern Databases (PDB).
Características Técnicas

    Algoritmo: IDA* para optimización de memoria y garantía de solución mínima.

    Heurística: Pattern Database (PDB) múltiple, utilizando el valor máximo entre patrones para asegurar la admisibilidad y consistencia.

    Hashing: Implementación de Zobrist Hashing para una indexación de estados abstractos rápida y sin colisiones.

    Lenguaje: C++ compilado con g++.

📂 Estructura del Proyecto

    src/: Archivos de implementación (.cpp).

    include/: Archivos de cabecera (.hpp).

    data/: Carpeta donde se almacenan las PDBs generadas en formato binario (.bin).

    obj/: Archivos objeto temporales.

Gemini dijo

¡Claro que sí! Vamos a preparar un README.md de nivel profesional. Este archivo es la cara de tu proyecto y el profesor Guillermo Palma valorará mucho que esté bien estructurado, ya que facilita la corrección y demuestra orden.

Respecto al archivo .bat: Sí, puedes eliminarlo, pero mi recomendación es que mejor lo actualices para que use el comando de g++. Así, el profesor solo tiene que darle doble clic para compilar todo sin escribir comandos manualmente.

Aquí tienes el contenido para tu README.md:
Agente de Búsqueda para el Rompecabezas TopSpin (12 piezas)

Este proyecto implementa un agente inteligente capaz de resolver el puzzle TopSpin de 12 piezas de forma óptima. Utiliza el algoritmo de búsqueda informada IDA* (Iterative Deepening A*) y una heurística basada en Pattern Databases (PDB).
🚀 Características Técnicas

    Algoritmo: IDA* para optimización de memoria y garantía de solución mínima.

    Heurística: Pattern Database (PDB) múltiple, utilizando el valor máximo entre patrones para asegurar la admisibilidad y consistencia.

    Hashing: Implementación de Zobrist Hashing para una indexación de estados abstractos rápida y sin colisiones.

    Lenguaje: C++ compilado con g++.

📂 Estructura del Proyecto

    src/: Archivos de implementación (.cpp).

    include/: Archivos de cabecera (.hpp).

    data/: Carpeta donde se almacenan las PDBs generadas en formato binario (.bin).

    obj/: Archivos objeto temporales.

🛠️ Requisitos e Instalación

El proyecto ha sido desarrollado para ser compilado con g++ (MinGW-w64/MSYS2).
1. Compilación

Desde la raíz del proyecto, ejecute el siguiente comando en su terminal:
Bash

g++ -O3 -I./include src/*.cpp -o topspin.exe 
     (El flag -O3 se incluye para optimizar la velocidad de la búsqueda).

🎮 Ejecución

El ejecutable recibe 13 argumentos: 12 números que representan el estado inicial y el nombre del archivo de salida.

./topspin.exe <n1> <n2> ... <n12> <archivo_salida> en linux
topspin.exe <n1> <n2> ... <n12> <archivo_salida> en windows


Ejemplo de uso 
./topspin.exe 7 6 2 3 8 1 5 9 10 11 12 4 salida.txt

Salida del Programa

    Consola (Estándar):

        Línea 1: Longitud del camino óptimo.

        Línea 2: Número de estados generados durante la búsqueda.

    Archivo de salida: Secuencia completa de estados desde el inicio hasta la meta (1 2 3 4 5 6 7 8 9 10 11 12)

Gemini dijo

¡Claro que sí! Vamos a preparar un README.md de nivel profesional. Este archivo es la cara de tu proyecto y el profesor Guillermo Palma valorará mucho que esté bien estructurado, ya que facilita la corrección y demuestra orden.

Respecto al archivo .bat: Sí, puedes eliminarlo, pero mi recomendación es que mejor lo actualices para que use el comando de g++. Así, el profesor solo tiene que darle doble clic para compilar todo sin escribir comandos manualmente.

Aquí tienes el contenido para tu README.md:
Agente de Búsqueda para el Rompecabezas TopSpin (12 piezas)

Este proyecto implementa un agente inteligente capaz de resolver el puzzle TopSpin de 12 piezas de forma óptima. Utiliza el algoritmo de búsqueda informada IDA* (Iterative Deepening A*) y una heurística basada en Pattern Databases (PDB).
🚀 Características Técnicas

    Algoritmo: IDA* para optimización de memoria y garantía de solución mínima.

    Heurística: Pattern Database (PDB) múltiple, utilizando el valor máximo entre patrones para asegurar la admisibilidad y consistencia.

    Hashing: Implementación de Zobrist Hashing para una indexación de estados abstractos rápida y sin colisiones.

    Lenguaje: C++ compilado con g++.

📂 Estructura del Proyecto

    src/: Archivos de implementación (.cpp).

    include/: Archivos de cabecera (.hpp).

    data/: Carpeta donde se almacenan las PDBs generadas en formato binario (.bin).

    obj/: Archivos objeto temporales.

🛠️ Requisitos e Instalación

El proyecto ha sido desarrollado para ser compilado con g++ (MinGW-w64/MSYS2).
1. Compilación

Desde la raíz del proyecto, ejecute el siguiente comando en su terminal:
Bash

g++ -O3 -I./include src/*.cpp -o topspin.exe

(El flag -O3 se incluye para optimizar la velocidad de la búsqueda).
🎮 Ejecución

El ejecutable recibe 13 argumentos: 12 números que representan el estado inicial y el nombre del archivo de salida.

Formato:
Bash

./topspin.exe <n1> <n2> ... <n12> <archivo_salida>

Ejemplo de uso:
Bash

./topspin.exe 7 6 2 3 8 1 5 9 10 11 12 4 salida.txt

Salida del Programa

    Consola (Estándar):

        Línea 1: Longitud del camino óptimo.

        Línea 2: Número de estados generados durante la búsqueda.

    Archivo de salida: Secuencia completa de estados desde el inicio hasta la meta (1 2 3 4 5 6 7 8 9 10 11 12).

🧠 Diseño de la Heurística

La heurística se basa en la abstracción del espacio de estados sugerida por Bortoluzzi. Se utilizan dos bases de datos de patrones (PDBs) que se generan la primera vez que se ejecuta el programa:

    PDB 1: Enfocada en las piezas {1, 2, 3, 4}.

    PDB 2: Enfocada en las piezas {9, 10, 11, 12}.

Al tomar el valor máximo entre ambas, se garantiza que la función sea admisible (nunca sobreestima el costo real a la meta), permitiendo que IDA* encuentre siempre el camino más corto.