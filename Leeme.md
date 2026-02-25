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

Estructura del Proyecto

    src/: Archivos de implementación (.cpp).
    include/: Archivos de cabecera (.hpp).
    data/: Carpeta donde se almacenan las PDBs generadas en formato binario (.bin).
    obj/: Archivos objeto temporales.

Descripción de los módulos

    1. state.cpp / state.hpp

        Este archivo define la estructura básica del puzzle.
        shiftLeft / shiftRight: Mueven todas las piezas del círculo una posición. Usamos std::rotate para que el movimiento sea eficiente.
        rotateK: Es la acción principal del TopSpin. Invierte el orden de las primeras 4 piezas del vector actual.
        isGoal: Una función rápida que chequea si los números ya están en orden del 1 al 12.

    2. solver.cpp / solver.hpp

        Aquí reside la lógica del algoritmo IDA*.
        solve: Es el punto de entrada. Inicia con un límite de costo (bound) y va llamando a la búsqueda recursiva. Si no encuentra la meta, sube el límite y vuelve a empezar.
        search: Es la función recursiva. Explora los estados, cuenta cuántos nodos vamos visitando y usa la heurística para decidir si vale la pena seguir por una rama o si mejor la "poda".
        heuristic: Aquí es donde ocurre la magia. Consulta las dos PDBs que creamos y elige el valor más alto (max). Esto es lo que garantiza que el agente no se pierda y encuentre siempre el camino más corto.
    
    3. pdb.cpp / pdb.hpp

        Este módulo se encarga de las "tablas de consulta" (Pattern Databases).
        generate: Crea la base de datos haciendo una búsqueda hacia atrás desde la meta. Es como si el programa practicara el puzzle muchas veces solo con algunas piezas para saber cuánto cuesta acomodarlas.
        saveToFile / loadFromFile: Guardan y cargan los resultados en archivos .bin Así, la segunda vez que corras el programa, entrará directo a resolver sin tener que calcular nada previo.
    
    4. utils.cpp / utils.hpp

        initZobrist / computeHash: Implementan el Hashing de Zobrist. En lugar de comparar 12 números cada vez, convertimos la posición de las piezas en un código único (un número gigante). Esto hace que buscar en la PDB sea casi instantáneo.
    
    5. main.cpp

        Su función es coordinar el flujo de trabajo desde que el usuario introduce los datos hasta que se obtiene la solución:
        ectura de parámetros: Captura los 12 números del estado inicial y el nombre del archivo de salida desde la línea de comandos.
        Inicialización de Heurística: Configura los patrones (piezas {1,2,3,4} y {9,10,11,12}) y prepara las bases de datos.
        Gestión de archivos PDB: Antes de resolver, chequea si ya existen los archivos .bin en la carpeta data/. Si están, los carga; si no, llama a la función de generación.
        Llamada al Solver: Crea la instancia del algoritmo IDA* con las piezas ingresadas y dispara la búsqueda.
        Reporte de resultados: Al finalizar, muestra por pantalla el tiempo, los nodos expandidos y guarda la secuencia de pasos en el archivo especificado.

Compilación

    Para compilar el proyecto de forma fácil y rápida e usa:
        g++ -O3 src/*.cpp -I./include -o topspin.exe
    nota: El flag -O3 le dice al compilador que optimice el código al máximo. Esto es vital porque IDA* genera miles de nodos por segundo y sin optimización tardaría mucho más.
    
Ejeución
    Para ejecutar 
        ./topspin.exe < números del 1 al 12 ubicados aleatoriamente separados por espacio> < nombre_archivo_salida.tx >
    