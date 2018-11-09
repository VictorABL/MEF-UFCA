
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


    typedef std::shared_ptr< FEM::LinearElastico<double> > shared_ptr_material;


    shared_ptr_material mat(new FEM::LinearElastico<double>("aco", 200E9, 0.3));

    typedef FEM::Analise<FEM::QuadrilateroIsoparametrico,FEM::LinearElastico, FEM::Ponto2D, double> analise;

    auto a = analise();

    std::vector<int> v = {0,1};
    a.CriarMalha(8, mat, 3E-3, 3);
    a.AdicionarApoio(0, v);
    a.AdicionarApoio(3, v);
    a.EnumerarGraus();

    analise::ptrLista_elementos::iterador it = a.GetElementos().begin();

    Imprimir(it->MatrizRigidezElementar());

    return 0;
}
