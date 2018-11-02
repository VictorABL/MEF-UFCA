
#ifndef ALGEBRA_H
#define ALGEBRA_H

#include "matrizes.h"

// Documentação para a definição das operações genéricas de álgebra linear e outras
// operações entre os elementos, tais como matrizes, vetores, etc..


namespace FEM {

// PRODUTO ESCALAR:
template<class T>
T ProdutoEscalar(FEM::EstruturaVetor<T> &vetor_a, FEM::EstruturaVetor<T> &vetor_b) {
    // Retorna o produto escalar entre dois vetores.
    T escalar;

    for(size_t iterator = 0; iterator < vetor_a.size(); iterator++)
        escalar += vetor_a(iterator) * vetor_b(iterator);

    return escalar;
}

// PRODUTO MATRIZ SIMÉTRICA CRS POR VETOR:
template<template<class T> class Estrutura, class Tipo>
FEM::EstruturaVetor<Tipo> ProdutoCRSporVetor(FEM::Matriz<Estrutura, Tipo> &matriz_a,FEM::EstruturaVetor<Tipo> &vetor_a) {
    // Função que retorna o vetor produto da multiplicação de uma matriz CRS e um vetor
    // essa operação foi separada devido à diferença de implementação do algoritmo.
    auto vetor_b = matriz_a.GetEstruturaDaMatriz().MultiplicarPorVetor(vetor_a);

    return std::move(vetor_b);
    }

// Implementação da função de multiplicação tripla entre matrizes,
// sendo dado por: B_t * C * B , onde B_t é a transposta de B.

template<template<class B> class Estrutura1, template<class C> class Estrutura2, class T>
FEM::Matriz<FEM::EstruturaMatrizSimetricaCheia, T> MultiplicacaoTripla(const FEM::Matriz<Estrutura1, T> &matriz_a,
    const FEM::Matriz<Estrutura2, T> &matriz_b, const T constante = 1) {

    // Inicialização da matriz de saída:
    FEM::Matriz<FEM::EstruturaMatrizSimetricaCheia, T> matriz_c(matriz_a.NumeroDeColunas(), matriz_a.NumeroDeColunas());

    // Variável auxiliar para as operações realizadas:
    T auxiliar;

    // Loop da matriz de retorno:
    for(size_t linha = 0; linha < matriz_c.NumeroDeLinhas(); linha++) {
        for(size_t coluna = 0; coluna < linha + 1; coluna++) {

            // Loop de multiplicacao dos elementos de B_t com C:
            for(size_t coluna2 = 0; coluna2 < matriz_b.NumeroDeColunas(); coluna2++) {
                auxiliar = 0.0;

                for(size_t linha2 = 0; linha2 < matriz_b.NumeroDeLinhas(); linha2++) {
                    auxiliar += matriz_a(linha2, coluna) * matriz_b(linha2, coluna2);
                }
                auxiliar *= matriz_a(coluna2, linha);
                matriz_c(linha, coluna) += auxiliar;
            }
            matriz_c(linha,coluna) *= constante;
        }
    }
    return std::move(matriz_c);
}

// Função de retorno da transposta da matriz:
template<template<class B> class Estrutura, class Tipo>
FEM::Matriz<Estrutura, Tipo> Transposta(const FEM::Matriz<Estrutura, Tipo> &matriz_a) {

    FEM::Matriz<Estrutura, Tipo> matrizTransposta(matriz_a.NumeroDeColunas(), matriz_a.NumeroDeLinhas());

    for(size_t linha = 0; linha < matrizTransposta.NumeroDeLinhas(); linha ++) {
        for(size_t coluna = 0; coluna < matrizTransposta.NumeroDeColunas(); coluna++) {
            matrizTransposta(linha, coluna) = matriz_a(coluna, linha);
        }
    }
    return std::move(matrizTransposta);
}
}

#endif
