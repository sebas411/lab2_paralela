#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include <cmath>

#define N 1000000
#define MAX 100000000
using namespace std;
int number_of_threads= 6;




void par_qsort(int *data, int lo, int hi) {
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
  
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}

int main(int argc, char * argv[]) {
    srand(time(0));

    int n = N, max = MAX;
    if (argc > 1) {
        n = stoi(argv[1]);
    }
    if (argc > 2) {
        max = stoi(argv[2]);
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
    //inicia la medicion del tiempo, tras haber leido los datos
    double start = omp_get_wtime();

    int sliceSize= round(n/number_of_threads);
    cout<< sliceSize << " ES el tamaño de los sub conjuntos"<< endl;
    #pragma omp parallel for num_threads(thread_count)
    for (int j = 0; j < number_of_threads;j++){
        int start = j*sliceSize;
        int end = (j+1)*sliceSize;
        //cout <<" El bloque numero"<< j << " empieza en"<<start<<" y termina en "<<end<< endl;
        par_qsort(Array,start,end);
    }
    par_qsort(Array, 0, n-1);




    double end = omp_get_wtime();
    double delta = end - start;

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

    cout << "El tiempo de ejecución para el programa paralelo 1 fue de " << delta << "s" << endl;
    numFileR.close();
    sortedFile.close();
    delete Array;

    return 0;
}