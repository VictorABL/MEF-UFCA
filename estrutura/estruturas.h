
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


#include <vector>
#include <math.h>
#include <utility>

// Documentação para a definição das estruturas de dados de matrizes
// e vetores. Todos os elementos utilizam a STL vector como conteiners.

// Implementação de uma estrutura de vetor padrão,
// utilizando a STL vector:

namespace FEM {

template<class T>

class EstruturaVetor {

    // primitivo de dado.
    // Implementação de uma estrutura de um vetor de qualquer tipo

private:
    // Definição do container de elementos e do tamanho do objeto:
    std::vector<T> elementos;
    size_t tamanho;

public:
    // Inicialização da classe de maneira parametrizada (construtor).
    EstruturaVetor(size_t tamanho, T inicializar = 0)
                  : elementos(tamanho, inicializar),
                    tamanho(tamanho) {}

    // Destrutor:
    ~EstruturaVetor() {}

    // Sobrecarga do operador () para indexação.
    T &operator() (size_t posicao) {
        return this->elementos[posicao];
    }

    // Para objetos contantes:
    const T &operator() (size_t posicao) const {
        return this->elementos[posicao];
    }

    // Retorna o tamanho atual do vetor.
    const size_t GetTamanho() {return tamanho;}

    // Adiciona um elemento ao final do vetor.
    void AdicionarElemento(const T elemento) {elementos.push_back(elemento); tamanho++;}

    // Remove o último elemento do vetor.
    void RemoverElemento() {elementos.pop_back(); tamanho--;}

    // Operação de multiplicação por escalar:
    void MultiplicarPorEscalar(const T escalar) {
        for(size_t iterador = 0; iterador < elementos.size(); iterador++)
        elementos[iterador] *= escalar;
    }
};

template<class T>
class EstruturaMatrizGenerica {

    // Estrutura de dados para a implementação de uma matriz genérica, utilizando
    // a classe STL vector para o armazenamento de dados:

private:
    // Container que contem todos os elementos da matriz:
    std::vector<T> elementos;
    // Dimensões do objeto:
    size_t numeroDeLinhas, numeroDeColunas;

public:
    // Inicialização da classe (construtor) é padrão, uma vez que
    // a classe é uma abstração para a conteção de dados.
    EstruturaMatrizGenerica(const size_t linhas = 1, const size_t colunas = 1)
                           : elementos(linhas * colunas),
                             numeroDeLinhas(linhas),
                             numeroDeColunas(colunas) {}

    // Destrutor:
    ~EstruturaMatrizGenerica() {}

    // Retorno das dimensões da matriz (Getters):
    const size_t GetLinhas() const {return numeroDeLinhas;}
    const size_t GetColunas() const {return numeroDeColunas;}

    // Sobrecarga do operador (), para instaciação dos elementos:
    T &GetElemento (size_t linha, size_t coluna) {
      // Retorna o elemento nas posições indicadas pelos
      // parâmetros da função.
      return elementos[(numeroDeColunas * linha) + coluna];
    }

    // No caso de objetos constantes:
    const T &GetElemento (size_t linha, size_t coluna) const {
      // Retorna o elemento nas posições indicadas pelos
      // parâmetros da função.
      return elementos[(numeroDeColunas * linha) + coluna];
    }


    // Operação de multiplicação por escalar:
    void MultiplicarPorEscalar(T escalar) {
        for(size_t iterador = 0; iterador < elementos.size(); iterador++)
            elementos[iterador] *= escalar;
    }

};

template<class T>
class EstruturaMatrizSimetricaCRS {

    // Estrutura para a implementação de uma matriz simétrica pelo
    // método Compressed Row Storage (CRS), utilizando também a classe
    // STL vector para o armazenamento de dados.

private:
    // Conteiner dos elementos da matriz:
    std::vector<T> elementos;
    // Vetor auxiliar para a posição dos elementos da diagonal principal no vetor elementos:
    std::vector<size_t> posicaoColunas;
    // Posição do elemento contada a partir do elemento da diagonal principal:
    std::vector<size_t> enderecoDiagonais;
    // Dimensões da matriz:
    size_t dimensoes;
    // Define um elemento zero padrão da matriz:
     T elementoZero = 0.0;

public:

    // A classe caracteriza uma forma organizacional, logo seus elementos são
    // adicionados progressivamente.

    // Construtor:
    EstruturaMatrizSimetricaCRS(const std::vector<T> &elemento, const std::vector<size_t> &posicaoColuna,
                                const std::vector<size_t> &enderecoDiagonal, const size_t dimensao = 1)

                                : elementos(elemento),
                                  posicaoColunas(posicaoColuna),
                                  enderecoDiagonais(enderecoDiagonal),
                                  dimensoes(dimensao)
                                  {enderecoDiagonais.push_back(posicaoColuna.size());}

    // Destrutor:
    ~EstruturaMatrizSimetricaCRS() {}

    // Retornam as dimensões:
    size_t GetLinhas() const {return dimensoes;}
    size_t GetColunas() const {return dimensoes;}

    // Retorna o elemento da matriz:
    T &GetElemento(size_t linha, size_t coluna) {
        if (coluna < linha) {
            // Como a função retorna os valores acima da diagonal, os índices primeiramente
            // são invertidos.
            std::swap(coluna, linha);
        }

        // Percorre os vetores auxiliares e analisa se há elemento diferente de zero:
        for(size_t posicao = enderecoDiagonais[linha]; posicao < enderecoDiagonais[linha + 1]; posicao++) {
            if (coluna - linha == posicaoColunas[posicao]){
                return elementos[posicao];
            }
        }
        // Se o elemento for igual a zero:
        return elementoZero;
    }

    // Para objetos constantes:
    const T &GetElemento(size_t linha, size_t coluna) const {
        if (coluna < linha) {
            // Como a função retorna os valores acima da diagonal, os índices primeiramente
            // são invertidos.
            std::swap(coluna, linha);
        }

        // Percorre os vetores auxiliares e analisa se há elemento diferente de zero:
        for(size_t posicao = enderecoDiagonais[linha]; posicao < enderecoDiagonais[linha + 1]; posicao++) {
            if (coluna - linha == posicaoColunas[posicao]){
                return elementos[posicao];
            }
        }
        // Se não for:
        return elementoZero;
    }

    // Operação de multiplicação por escalar:
    void MultiplicarPorEscalar(const T escalar) {
        for(size_t iterador = 0; iterador < elementos.size(); iterador++)
            elementos[iterador] *= escalar;
    }

    // Multiplicação da matriz em modo CRS por um vetor genérico:
    EstruturaVetor<T> MultiplicarPorVetor(const EstruturaVetor<T> &vetor_a) {

        EstruturaVetor<T> vetor_b(vetor_a.GetTamanho(),0);

        for(size_t linha = 0; linha < vetor_b.GetTamanho(); linha++) {
            vetor_b(linha) += elementos[enderecoDiagonais[linha]] * vetor_a(linha);

            for(size_t iterador = enderecoDiagonais[linha] + 1; iterador < enderecoDiagonais[linha + 1]; iterador++) {
                vetor_b(linha) += elementos[iterador] * vetor_a(posicaoColunas[iterador]);
                vetor_b(posicaoColunas[iterador]) += elementos[iterador] * vetor_a(linha);
            }
        }

        return std::move(vetor_b);
    }

};

template<class T>
class EstruturaMatrizSimetricaCheia {

    // Definição para e estrutura de uma matriz simétrica cheia,
    // com a indexação da metades de seus elementos,
    // a diferença em relação ao método CRS simétrica é que há a representação
    // dos elementos nulos da matriz.

private:
    // Inicialização dos elementos e das dimensões:
    size_t numeroDeLinhas, numeroDeColunas;
    std::vector<T> elementos;

public:

    // Construtor:
    EstruturaMatrizSimetricaCheia(size_t linhas = 1, size_t colunas = 1)
                                 : elementos(((2 + linhas) * linhas)/2, 0),
                                 numeroDeLinhas(linhas),
                                 numeroDeColunas(colunas) {}

    // Destrutor:
    ~EstruturaMatrizSimetricaCheia() {}

    // Retorna as dimensões da matriz.
    size_t GetLinhas() const {return numeroDeLinhas;}
    size_t GetColunas() const {return numeroDeColunas;}

    // Função de indexação:
    T &GetElemento(size_t linha, size_t coluna) {
        if (coluna > linha) {
            std::swap(coluna, linha);
        }

        return elementos[(((1 + linha) * linha)/2) + coluna];
    }

    // Para objetos constantes:
    const T &GetElemento(size_t linha, size_t coluna) const {
        if (coluna > linha) {
            std::swap(coluna, linha);
        }

        return elementos[(((1 + linha) * linha)/2) + coluna];
    }

    // Multiplicar por escalar:
    void MultiplicarPorEscalar(const T escalar) {
        for(size_t iterador = 0; iterador < elementos.size(); iterador++)
            elementos[iterador] *= escalar;
    }

};
}

#endif
