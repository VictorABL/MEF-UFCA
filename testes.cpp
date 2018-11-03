
#include<iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>

#include "estruturas.h"
#include "matrizes.h"
#include "algebra.h"
#include "ponto.h"
#include "graus.h"
#include "no.h"
#include "materiais.h"
#include "apoio.h"
#include "quadratura.h"
#include "geometrias.h"

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

    // Criação dos Pontos:
    FEM::Ponto2D<> p1({1,10.0});
    FEM::Ponto2D<> p2({-1.0,-1.0});
    FEM::Ponto2D<> p3({-1.0,1.0});
    FEM::Ponto2D<> p4({-1.0,3.0});

    // Criação dos nós:
    boost::ptr_vector<FEM::No<FEM::Ponto2D, double> > vetor;
    vetor.push_back(new FEM::No<FEM::Ponto2D, double>(p1, 3));
    vetor.push_back(new FEM::No<FEM::Ponto2D, double>(p2, 3));
    vetor.push_back(new FEM::No<FEM::Ponto2D, double>(p3, 3));
    vetor.push_back(new FEM::No<FEM::Ponto2D, double>(p4, 3));


    double CP = 0.35, ME = 236E9, EP = 3E-3;
    FEM::Material<> m1("aco", ME, CP);

    // Inplementação do elemento(4 nós):
    FEM::QuadrilateroIsoparametrico<> quadrado(vetor, m1, EP);
    auto K = quadrado.MatrizRigidezElementar();
    // Imprimir(K);

    // Apoios:
    std::vector<int> v = {0,2};

    auto a1 = FEM::Apoio<FEM::Ponto2D, double>(vetor[0], v);
    auto a2 = FEM::Apoio<FEM::Ponto2D, double>(vetor[2], v);

    // Indexação dos graus de liberdade de cada nó:
    using it = boost::ptr_vector< FEM::No<FEM::Ponto2D, double> >::iterator;
    for(it i = vetor.begin(); i != vetor.end(); i++) {
        (*i).EnumeraGrausDeLiberdade();
    }

    for(size_t i = 0; i < vetor.size(); i++) {
        for(size_t j = 0; j < vetor.size() - 1; j++)
            std::cout << vetor[i].GetVetorGrausDeLiberdade()[j] << '\n';
    }

    return 0;
}
