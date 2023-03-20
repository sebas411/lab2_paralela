#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <omp.h>

#define N 10000000
#define MAX 100000000
#define THREAD_NUM 4
using namespace std;

void par_qsort(int *data, int lo, int hi, int recursion_num=0) {
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l <= h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  
#pragma omp task if(recursion_num < 10) untied
  par_qsort(data, lo, h, recursion_num + 1);
#pragma omp task if(recursion_num < 10) untied
  par_qsort(data, l, hi, recursion_num + 1);
#pragma omp taskwait
}

int main(int argc, char * argv[]) {
    srand(time(0));

    int n = N, max = MAX, threads = THREAD_NUM;
    if (argc > 1) {
        n = stoi(argv[1]);
    }
    if (argc > 2) {
        max = stoi(argv[2]);
    }
    if (argc > 3) {
        threads = stoi(argv[3]);
    }

    ofstream numFile("num.csv",ios::out);
    if( numFile.bad() ) {
        cerr << "Error en la creación/escritura de archivo" <<endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < (n - 1); i++){
        numFile << rand() % (max + 1) << ",";
    }

    numFile << rand() % (max + 1);
    numFile.close();

    cout << n << " números random generados y guardados en num.csv" << endl;

    ifstream numFileR;
    numFileR.open("num.csv");
    if( numFileR.bad() ) {
        cerr << "Error al leer el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    int *Array = new int[n];
    string ch;
    for (int i = 0; i < n; i++) {
        getline(numFileR, ch, ',');
        Array[i] = stoi(ch);
    }
    double start = omp_get_wtime(); // iniciar medición de tiempo
#pragma omp parallel num_threads(threads)
    { // start omp parallel
#pragma omp single
    { // start omp single
    par_qsort(Array, 0, n-1);
    } // end omp single
    } // end omp parallel
    double end = omp_get_wtime();
    double delta = end - start;
    cout << "El tiempo de ejecución para el programa paralelo, usando "<< threads <<" hilos fue de " << delta << "s" << endl;
    ofstream sortedFile;
    sortedFile.open("sorted.csv");
    if ( sortedFile.bad() ) {
        cerr << "Error en la creación/escritura del archivo" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (n-1); i++) {
        sortedFile << Array[i] << ',';
    }
    sortedFile << Array[n-1] << endl;

    cout << "Datos ordenados y guardados en sorted.csv" << endl;

    numFileR.close();
    sortedFile.close();
    delete Array;

    return 0;
}