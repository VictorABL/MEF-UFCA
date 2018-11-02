
#include "algebra.h"

// Inplementação da classe da integração pela quadratura de gauss,
// utilizando as matrizes dos elementos do programa.

namespace FEM {

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
class QuadraturaDeGauss {

    // Classe abstrata para a integração dos componentes dos elementos,
    // analisa a dimensão, e inicia a função de integração com base em
    // tal análise.

private:
    static std::vector<double> xi1;
    static std::vector<double> xi2;
    static std::vector<double> xi3;
    static std::vector<double> xi4;
    static std::vector<std::vector<double> > xi;
    static std::vector<double> weight1;
    static std::vector<double> weight2;
    static std::vector<double> weight3;
    static std::vector<double> weight4;
    static std::vector<std::vector<double> > weight;

public:

    QuadraturaDeGauss() {}

    static FEM::Matriz<Estrutura> Integral(const TipoDeElemento<T> &Elemento, const int numeroDePontos) {

        // Inicialização da matriz de saída:
        FEM::Matriz<Estrutura, T> K;

        // Análise da dimensão do elemento:
        switch(Elemento.Dimensao()) {
            case 1:
                K = IntegralDimensao1(Elemento, numeroDePontos);
            case 2:
                K = IntegralDimensao2(Elemento, numeroDePontos);
            case 3:
                K = IntegralDimensao3(Elemento, numeroDePontos);
        }
        return std::move(K);
    }

    static auto IntegralDimensao1(const TipoDeElemento<T> &Elemento,
    const int numeroDePontos) -> decltype(Elemento.ProdutoTriplo(xi[numeroDePontos][0])) {

        auto K = Elemento.ProdutoTriplo(xi[numeroDePontos - 1][0]);

        K *= weight[numeroDePontos - 1][0];

        for (size_t i=1; i<numeroDePontos; i++)
        {
            K += Elemento.ProdutoTriplo(xi[numeroDePontos - 1][i]);
            K *= weight[numeroDePontos - 1][i];
        return std::move(K);
        }
    }


    static auto IntegralDimensao2(const TipoDeElemento<T> &Elemento,
    const int numeroDePontos) -> decltype(Elemento.ProdutoTriplo(xi[numeroDePontos][0], xi[numeroDePontos][0])) {

        auto K = Elemento.ProdutoTriplo(xi[numeroDePontos - 1][0], xi[numeroDePontos - 1][0]);

        K *= weight[numeroDePontos - 1][0]*weight[numeroDePontos - 1][0];

        for (size_t i = 0; i < numeroDePontos; i++)
        {
            for (size_t j = 0; j < numeroDePontos; j++)
            {
                if(!(i == 0 && j == 0)) {
                    K += Elemento.ProdutoTriplo(xi[numeroDePontos - 1][i], xi[numeroDePontos - 1][j]);
                    K *= weight[numeroDePontos - 1][i]*weight[numeroDePontos - 1][j];
                }
            }
        }
        return std::move(K);
    }

    static auto IntegralDimensao3(const TipoDeElemento<T> &Elemento,
    const int numeroDePontos) -> decltype(Elemento.ProdutoTriplo(xi[numeroDePontos][0],
    xi[numeroDePontos][0], xi[numeroDePontos][0])) {

        auto K = Elemento.ProdutoTriplo(xi[numeroDePontos - 1][0],
        xi[numeroDePontos - 1][0], xi[numeroDePontos - 1][0]);

        K *= weight[numeroDePontos - 1][0]* weight[numeroDePontos - 1][0] * weight[numeroDePontos - 1][0];

        for (size_t i = 0; i < numeroDePontos; i++)
        {
            for (size_t j = 0; j < numeroDePontos; j++)
            {
                for (size_t k = 0; k < numeroDePontos; k++){
                    if(!(i == 0 && j == 0 && k == 0)) {
                        K += Elemento.ProdutoTriplo(xi[numeroDePontos - 1][i], xi[numeroDePontos - 1][j], xi[numeroDePontos - 1][k]);
                        K *= weight[numeroDePontos - 1][i]*weight[numeroDePontos - 1][j]*weight[numeroDePontos - 1][k];
                    }
                }
            }
        }
        return std::move(K);
    }
};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::xi1= {0};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::xi2= {-1/sqrt(3), 1/sqrt(3)};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::xi3= {0};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::xi4= {0};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<std::vector<double> > FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::xi= {xi1, xi2, xi3, xi4};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::weight1= {2};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::weight2= {1, 1};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::weight3= {0};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<double> FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::weight4= {0};

template<template<class B> class TipoDeElemento, template<class B> class Estrutura, class T>
std::vector<std::vector<double> > FEM::QuadraturaDeGauss<TipoDeElemento, Estrutura, T>::weight= {weight1, weight2, weight3, weight4};

}
