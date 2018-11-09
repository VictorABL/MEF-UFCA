
#ifndef MEF_UFCA_CRS_H
#define MEF_UFCA_CRS_H

#include <vector>
#include <math.h>
#include <utility>


namespace FEM{

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
}

#endif
