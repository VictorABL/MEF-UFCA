
#ifndef VETOR_H
#define VETOR_H

#include <vector>
#include <math.h>
#include <utility>

namespace FEM {

template<class T>
class EstruturaVetor {

    // Implementação de uma estrutura de um vetor de qualquer tipo
    // primitivo de dado.

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
}

#endif
