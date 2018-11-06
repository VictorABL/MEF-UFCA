
#ifndef  SIMETRICA_H
#define  SIMETRICA_H

#include <vector>
#include <math.h>
#include <utility>


namespace FEM {

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
