//Raul Martinez Llorente

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix_stub.h"

int main(){

    multmatrix_stub* mmatrix = new multmatrix_stub();


    matrix_t* m1 = mmatrix->createRandMatrix(5,5);
    std::cout<<"Matriz aleatoria creada\n";
    matrix_t* m2 = mmatrix->createIdentity(5,5);
    std::cout<<"Matriz identidad creada\n";
    matrix_t* mres = mmatrix->multMatrices(m1,m2);
    std::cout<<"Multiplicacion matrices hecha\n";
    mmatrix->writeMatrix(mres,"resultado.txt");
    std::cout<<"resultado.txt escrito con matriz resultante 1\n";
    matrix_t* m3 = mmatrix->readMatrix("resultado.txt");
    std::cout<<"resultado.txt leido\n";
    matrix_t* mres2 = mmatrix->multMatrices(m1,m3);
    std::cout<<"Multiplicacion matrices 2 hecha\n";
    mmatrix->writeMatrix(mres2,"resultado2.txt");
    std::cout<<"resultado2.txt escrito con matriz resultante 2\n";
    
    delete m1;
    delete m2;
    delete mres;
    delete m3;
    delete mres2;
    delete mmatrix;
    
    return 0;

}
