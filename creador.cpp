#include <unistd.h>     //std lib
#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string

#define INFILE "numeros.csv"
int limit = 1000;


using namespace std;

int main(int argc, char * argv[]) {

    ofstream escribirNumeros(INFILE,ios::out);
    if( escribirNumeros.bad() ) {
        //cerr<<"Falló la creación del archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }

    //Llenamos el archivo INFILE con números
    for(int i=0; i<limit;i++){
        escribirNumeros<<i<<",";
    }
    escribirNumeros<<limit<<endl;
    escribirNumeros.close();

}