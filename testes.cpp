
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


    FEM::Ponto2D<double> p1({1.0,1.0});
    FEM::Ponto2D<double> p2({-1,11.0});
    FEM::Ponto2D<double> p3({2,5.6});
    FEM::Ponto2D<double> p4({2,3});
    FEM::Ponto2D<double> p5({3,3});

    FEM::LinearElastico<double> mat("aco", 200E9, 0.3);

    typedef std::shared_ptr<FEM::No<FEM::Ponto2D, double> > shared_ptr;
    typedef FEM::No<FEM::Ponto2D, double> ponto_2;

    // FEM::VetorPonteiro<FEM::No<FEM::Ponto2D, double> > v;
    FEM::ListaPonteiro<FEM::No<FEM::Ponto2D, double> > l;

    l.AdicionarFinal(shared_ptr(new FEM::No<FEM::Ponto2D, double>(p1, 3)));
    l.AdicionarFinal(shared_ptr(new FEM::No<FEM::Ponto2D, double>(p2, 3)));
    l.AdicionarFinal(shared_ptr(new FEM::No<FEM::Ponto2D, double>(p3, 3)));
    l.AdicionarFinal(shared_ptr(new FEM::No<FEM::Ponto2D, double>(p4, 3)));

    FEM::Face<FEM::Ponto2D, double> f1(l);
    std::shared_ptr<FEM::Face<FEM::Ponto2D, double> > f2(new FEM::Face<FEM::Ponto2D, double>(l));

    // auto e1 = FEM::QuadrilateroIsoparametrico<FEM::LinearElastico, double>(f2, mat, 3E-3);
    // auto k = e1.MatrizRigidezElementar();
    // Imprimir(k);

    auto a = FEM::Analise<FEM::QuadrilateroIsoparametrico,FEM::LinearElastico, FEM::Ponto2D, double>(8, mat, 3E-3, 3);

    std::vector<int> v = {0,1};
    a.CriarMalha();
    a.AdicionarApoio(0, v);
    a.AdicionarApoio(3, v);
    a.EnumerarGraus();

    return 0;
}
