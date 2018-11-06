
#ifndef GENERICA_H
#define GENERICA_H

#include <vector>
#include <math.h>
#include <utility>


namespace FEM{

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
}

#endif
