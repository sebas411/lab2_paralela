# Laboratorio 2 - OpenMP
## Integrantes
* Sebastián Maldonado 18003
* Pablo Coutiño 18817
## Compilación
* Secuencial:
    ```
    g++ clasificador_sec.cpp -fopenmp -o clasificador_sec
    ```
* Paralelo:
    ```
    g++ clasificador_par.cpp -fopenmp -o clasificador_par
    ```
## Ejecución
* Secuencial:
    ```
    ./clasificador_sec N max_rand
    ```
* Paralelo:
    ```
    ./clasificador_par N max_rand
    ```