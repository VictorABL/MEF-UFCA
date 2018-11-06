
#include<iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>

#include "includes.h"
#define EXPECT_EQUAL(test, expect) equalityTest( test, expect, \
                                                #test, #expect, \
                                                __FILE__, __LINE__)


// Imprime a matriz na tela:
template<template<class Ta>class Est, class T>
void Imprimir(const FEM::Matriz<Est, T> &matriz_a) {

    for(size_t linha = 0; linha < matriz_a.NumeroDeLinhas(); linha++) {
        for(size_t coluna = 0; coluna < matriz_a.NumeroDeColunas(); coluna++) {
            std::cout << matriz_a(linha, coluna) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {

    FEM::LinearElastico<double> mat("aco", 200E9, 0.3);

    auto a = FEM::Analise<FEM::QuadrilateroIsoparametrico,FEM::LinearElastico, FEM::Ponto2D, double>(8, mat, 3E-3, 3);

    std::vector<int> v = {0,1};
    a.CriarMalha();
    a.AdicionarApoio(0, v);
    a.AdicionarApoio(3, v);
    a.EnumerarGraus();

    return 0;
}
