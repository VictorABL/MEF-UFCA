
#ifndef MATRIZES_H
#define MATRIZES_H


#include "crs.h"
#include "generica.h"
#include "simetrica.h"
#include "vetor.h"

// Documentação das classes de matrizes do programa.


namespace FEM {

template<template<class T>class Estrutura = FEM::EstruturaMatrizGenerica, class Tipo = double>
class Matriz {

    // Classe de tipo padrão de matriz, a qual pode ser definida por várias
    // estruturas diferentes, como a própria genérica, simétrica, etc...

public:

    typedef typename Matriz<FEM::EstruturaMatrizGenerica, Tipo> matriz_generica;


private:

    Estrutura<Tipo> dadosDaMatriz;

public:

    // Inicialização da classe matriz:
    Matriz(const size_t linhas, const size_t colunas): dadosDaMatriz(linhas, colunas) {}

    // Para matrizes simétricas, sobrecarga para a dimensão especificada:
    Matriz(const size_t dimensao = 1): dadosDaMatriz(dimensao, dimensao) {}

    // Sobrecarga do operador () para indexação dos elementos:
    // Para o caso de objetos constantes:
    Tipo &operator() (size_t linha, size_t coluna) {
        return dadosDaMatriz.GetElemento(linha, coluna);
    }

    const Tipo &operator() (size_t linha, size_t coluna) const {
        return dadosDaMatriz.GetElemento(linha, coluna);
    }

    // Retornar dimensões:
    const size_t NumeroDeLinhas() const {return dadosDaMatriz.GetLinhas();}
    const size_t NumeroDeColunas() const {return dadosDaMatriz.GetColunas();}

    // Sobrecarga de operador para multiplicação por escalar:
    Matriz &operator*= (Tipo escalar) {
        dadosDaMatriz.MultiplicarPorEscalar(escalar);
        return *this;
    }

    // Cálculo da transposta da matriz:
    Matriz<Estrutura, Tipo> Transposta() {

        Matriz<Estrutura, Tipo> matrizTransposta(NumeroDeColunas(), NumeroDeLinhas());

        for(size_t linha = 0; linha < matrizTransposta.NumeroDeLinhas(); linha ++) {
            for(size_t coluna = 0; coluna < matrizTransposta.NumeroDeColunas(); coluna++) {
                matrizTransposta(linha, coluna) = dadosDaMatriz.GetElemento(coluna, linha);
            }
        }

        return std::move(matrizTransposta);
    }

    // Operação de soma entre matrizes:
    template<template<class B> class Estrutura2, class Tipo2>
    matriz_generica operator+ (const Matriz<Estrutura2, Tipo2> &matriz_a) {

        matriz_generica matriz_c(NumeroDeLinhas(), NumeroDeColunas());

        for(size_t linha = 0; linha < NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < NumeroDeColunas(); coluna++)
                matriz_c(linha, coluna) = matriz_a(linha, coluna) +
                                          dadosDaMatriz.GetElemento(linha, coluna);
        }

        return std::move(matriz_c);

    }

    // Operação de multiplicação entre matrizes:
    template<template<class C> class Estrutura2, class T2>
    matriz_generica operator*(const Matriz<Estrutura2, T2> &matriz_a) {
        // Operação de multiplicação genérica para qualquer objeto matriz instanciado em
        // diferentes estruturas.
        matriz_generica matriz_c(NumeroDeLinhas(), matriz_a.NumeroDeColunas());

        for(size_t linha = 0; linha < matriz_c.NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < matriz_c.NumeroDeColunas(); coluna++) {
                for(size_t vez = 0; vez < NumeroDeColunas(); vez++)
                    matriz_c(linha,coluna) += dadosDaMatriz.GetElemento(linha, vez) *
                                              matriz_a(vez, coluna);
            }
        }
        return std::move(matriz_c);
    }

    // Operação de incrementação da matriz por outra:
    template<template<class C> class Estrutura2, class T2>
    Matriz &operator += (const Matriz<Estrutura2, T2> &matriz_a) {
        for(size_t linha = 0; linha < NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < NumeroDeColunas(); coluna++){
                dadosDaMatriz.GetElemento(linha, coluna) += matriz_a(linha, coluna);
            }
        }
        return *this;
    }

};

// Especialização parcial da classe matriz para a estrutura
// da matriz simétrica CRS.

template<class Tipo>
class Matriz<FEM::EstruturaMatrizSimetricaCRS, Tipo> {

    // Classe de tipo padrão de matriz, a qual pode ser definida por várias
    // estruturas diferentes, como a própria genérica, CRS, etc...

public:

    typedef typename Matriz<FEM::EstruturaMatrizGenerica, Tipo> matriz_generica;

private:

    FEM::EstruturaMatrizSimetricaCRS<Tipo> dadosDaMatriz;

public:

    // Inicialização da classe matriz:
    Matriz(const std::vector<Tipo> &elementos, const std::vector<size_t> &posicaoColunas,
                    const std::vector<size_t> &enderecoDiagonais,const size_t dimensao = 1)

          : dadosDaMatriz(elementos, posicaoColunas,
                          enderecoDiagonais, dimensao) {}

    // Sobrecarga do operador () para indexação dos elementos:
    // Para o caso de objetos constantes:
    Tipo &operator() (size_t linha, size_t coluna) {
        return dadosDaMatriz.GetElemento(linha, coluna);
    }

    const Tipo &operator() (size_t linha, size_t coluna) const {
        return dadosDaMatriz.GetElemento(linha, coluna);
    }

    // Retornar dimensões:
    size_t NumeroDeLinhas() const {return dadosDaMatriz.GetLinhas();}
    size_t NumeroDeColunas() const {return dadosDaMatriz.GetColunas();}

    // Sobrecarga de operador para multiplicação por escalar:
    Matriz &operator*= (Tipo escalar) {
        dadosDaMatriz.MultiplicarPorEscalar(escalar);
        return *this;
    }

    // Operação de soma entre matrizes:
    template<template<class B> class Estrutura2, class Tipo2>
    matriz_generica operator+ (const Matriz<Estrutura2, Tipo2> &matriz_a) {

        matriz_generica matriz_c(NumeroDeLinhas(), NumeroDeColunas());

        for(size_t linha = 0; linha < NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < NumeroDeColunas(); coluna++)
                matriz_c(linha, coluna) = matriz_a(linha, coluna) +
                                          dadosDaMatriz.GetElemento(linha, coluna);
        }

        return std::move(matriz_c);
    }

    // Operação de multiplicação entre matrizes:
    template<template<class C> class Estrutura2, class T2>
    matriz_generica operator*(const Matriz<Estrutura2, T2> &matriz_a) {
        // Operação de multiplicação genérica para qualquer objeto matriz instanciado em
        // diferentes estruturas.
        matriz_generica matriz_c(NumeroDeLinhas(), matriz_a.NumeroDeColunas());

        for(size_t linha = 0; linha < matriz_c.NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < matriz_c.NumeroDeColunas(); coluna++) {
                for(size_t vez = 0; vez < NumeroDeColunas(); vez++)
                    matriz_c(linha,coluna) += dadosDaMatriz.GetElemento(linha, vez) *
                                              matriz_a(vez, coluna);
            }
        }
        return std::move(matriz_c);
    }

    // Operação de incrementação da matriz por outra:
    template<template<class C> class Estrutura2, class T2>
    Matriz &operator += (const Matriz<Estrutura2, T2> &matriz_a) {
        for(size_t linha = 0; linha < NumeroDeLinhas(); linha++) {
            for(size_t coluna = 0; coluna < NumeroDeColunas(); coluna++){
                dadosDaMatriz.GetElemento(linha, coluna) += matriz_a(linha, coluna);
            }
        }
        return *this;
    }
};
}

#endif
