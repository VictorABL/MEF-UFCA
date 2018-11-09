
#ifndef GEOMETRIAS_H
#define GEOMETRIAS_H

#include<vector>
#include <boost/iterator/indirect_iterator.hpp>

#include "dois_d.h"
#include "tres_d.h"
#include "graus.h"
#include "no.h"

#include "elastico_lin.h"
#include "quadratura.h"

// Documentação dos elementos componentes das estruturas,
// inicialmente de formato bidimensional, tais como
// quadriláteros, triângulos e etc.

namespace FEM {

template<template<class B> class Material, class T = double>
class QuadrilateroIsoparametrico {

    // Definição da classe de um elemento bidimensional, com
    // quatro nós (quadrilátero) e isoparamétrico.

public:

    typedef typename FEM::QuadraturaDeGauss<QuadrilateroIsoparametrico, LinearElastico,
                                            FEM::EstruturaMatrizSimetricaCheia, T> integracao;

    typedef typename FEM::Matriz<FEM::EstruturaMatrizSimetricaCheia, T> matriz_sim;

    typedef typename FEM::Matriz<FEM::EstruturaMatrizGenerica, T> matriz;


    typedef typename FEM::ListaPonteiro<FEM::No<FEM::Ponto2D, T> > ptrLista;

    typedef typename std::shared_ptr<FEM::Face<FEM::Ponto2D, T> > ptr_face;

    typedef typename std::shared_ptr<Material<T> > ptr_material;

private:

    // Ponteiro da face do elemento na malha:
    ptr_face nosDoElemento;
    // Classe de características físicas do material.
    ptr_material material;
    // Inicialização da variável da matriz característica do elemento:
    matriz matrizConstitutiva;
    T espessura;
    // Dimensão do elemento:
    int dimensao = 2;


    // #################################################################################################################
    // #################################################################################################################


    // Função de inicialização da matriz de forma do elemento:
    matriz DefinirMatrizDeForma(const T pontoX, const T pontoY) const {

        // Definição funções de forma:
        T N1 = (1.0/4.0)*(1.0 - pontoX) * (1.0 - pontoY);
        T N2 = (1.0/4.0)*(1.0 + pontoX) * (1.0 - pontoY);
        T N3 = (1.0/4.0)*(1.0 + pontoX) * (1.0 + pontoY);
        T N4 = (1.0/4.0)*(1.0 - pontoX) * (1.0 + pontoY);

        // Implementação na matriz:
        matriz MatrizDeForma(2,8);

        MatrizDeForma(0,0) = N1; MatrizDeForma(1,1) = N1;
        MatrizDeForma(0,2) = N2; MatrizDeForma(1,3) = N2;
        MatrizDeForma(0,4) = N3; MatrizDeForma(1,5) = N3;
        MatrizDeForma(0,6) = N4; MatrizDeForma(1,7) = N4;

        return std::move(MatrizDeForma);
    }


    matriz MatrizJacobiana(const T pontoX, const T pontoY) const {

        // Função que implementa a matriz jacobiana com base nas coordenadas naturais
        // e geométricas, de maneira direta.

        matriz matrizJacobiana(4,4);

        auto nos = this->GetCoordenada();

        matrizJacobiana(0,0) = (((1.0 - pontoY)/4.0) * (nos[1].GetCoordenadas()[0] -
                                nos[0].GetCoordenadas()[0])) + (((1.0 + pontoY)/4.0) *
                                (nos[2].GetCoordenadas()[0] - nos[3].GetCoordenadas()[0]));

        matrizJacobiana(0,1) = (((1.0 - pontoY)/4.0) * (nos[1].GetCoordenadas()[1] -
                                nos[0].GetCoordenadas()[1])) + (((1.0 + pontoY)/4.0) *
                                (nos[2].GetCoordenadas()[1] - nos[3].GetCoordenadas()[1]));

        matrizJacobiana(1,0) = (((1.0 - pontoX)/4.0) * (nos[3].GetCoordenadas()[0] -
                                nos[0].GetCoordenadas()[0])) + (((1.0 + pontoX)/4.0) *
                                (nos[2].GetCoordenadas()[0] - nos[1].GetCoordenadas()[0]));

        matrizJacobiana(1,1) = (((1.0 - pontoX)/4.0) * (nos[3].GetCoordenadas()[1] -
                                nos[0].GetCoordenadas()[1])) + (((1.0 + pontoX)/4.0) *
                                (nos[2].GetCoordenadas()[1] - nos[1].GetCoordenadas()[1]));


        return std::move(matrizJacobiana);
    }

    // Calcula o determinante da matriz jacobiana.
    T DeterminanteMatrizJacobiana(const matriz &matrizJacobiana) const
    {return (matrizJacobiana(0,0) * matrizJacobiana(1,1)) - (matrizJacobiana(0,1) * matrizJacobiana(1,0));}


    // Implementação da matriz jacobiana inversa:
    matriz MatrizJacobianaInversa(const matriz &matrizJacobiana, const T &determinanteMatrizJacobiana) const {

        // Função que implementa a matriz jacobiana inversa.
        matriz matrizJacobianaInversa(4,4);

        // Inserção dos valores dos elementos.
        matrizJacobianaInversa(0,0) = (1.0/determinanteMatrizJacobiana) * matrizJacobiana(1,1);
        matrizJacobianaInversa(0,1) = (1.0/determinanteMatrizJacobiana) * (-matrizJacobiana(0,1));
        matrizJacobianaInversa(1,0) = (1.0/determinanteMatrizJacobiana) * (-matrizJacobiana(1,0));
        matrizJacobianaInversa(1,1) = (1.0/determinanteMatrizJacobiana) * matrizJacobiana(0,0);

        return std::move(matrizJacobianaInversa);

    }

    matriz MatrizH(const matriz &matrizJacobianaInversa) const {

        // FEM::Matriz H é composta pelo inverso do jacobiano, disposto no primeiro e
        // quarto quadrante da matriz.

        matriz matrizH(4,4);

        matrizH(0,0) = matrizJacobianaInversa(0,0);
        matrizH(0,1) = matrizJacobianaInversa(0,1);
        matrizH(1,0) = matrizJacobianaInversa(1,0);
        matrizH(1,1) = matrizJacobianaInversa(1,1);
        matrizH(2,2) = matrizJacobianaInversa(0,0);
        matrizH(2,3) = matrizJacobianaInversa(0,1);
        matrizH(3,2) = matrizJacobianaInversa(1,0);
        matrizH(3,3) = matrizJacobianaInversa(1,1);

        return std::move(matrizH);
    }

    // Cálculo da matriz deformação:
    matriz MatrizDeformacao(const T pontoX, const T pontoY) const {

        matriz matrizDeformacao(4,8);

        matrizDeformacao(0,0) = -1.0 / 4.0 + pontoY / 4.0;
        matrizDeformacao(0,2) = 1.0 / 4.0 - pontoY / 4.0;
        matrizDeformacao(0,4) = pontoY / 4.0 + 1.0 / 4.0;
        matrizDeformacao(0,6) = -pontoY / 4.0 - 1.0 / 4.0;
        matrizDeformacao(1,0) = -1.0 / 4.0 + pontoX / 4.0;
        matrizDeformacao(1,2) = -pontoX / 4.0 - 1.0 / 4.0;
        matrizDeformacao(1,4) = pontoX / 4.0 + 1.0 / 4.0;
        matrizDeformacao(1,6) = 1.0 / 4.0 - pontoX / 4.0;
        matrizDeformacao(2,1) = -1.0 / 4.0 + pontoY / 4.0;
        matrizDeformacao(2,3) = 1.0 / 4.0 - pontoY / 4.0;
        matrizDeformacao(2,5) = pontoY / 4.0 + 1.0 / 4.0;
        matrizDeformacao(2,7) = -pontoY / 4.0 - 1.0 / 4.0;
        matrizDeformacao(3,1) = -1.0 / 4.0 + pontoX / 4.0;
        matrizDeformacao(3,3) = -pontoX / 4.0 - 1.0 / 4.0;
        matrizDeformacao(3,5) = pontoX / 4.0 + 1.0 / 4.0;
        matrizDeformacao(3,7) = 1.0 / 4.0 - pontoX / 4.0;

        return std::move(matrizDeformacao);
    }

    // Cálculo da matriz cinemática B:
    matriz MatrizCinematica(const T pontoX, const T pontoY, const matriz &matrizJacobianaInversa) const {

        // Inicialização das matrizes de deformação e da matriz H:
        auto matrizH = MatrizH(matrizJacobianaInversa);
        auto matrizDeDeformacao = MatrizDeformacao(pontoX, pontoY);

        // Inicializção da matriz auxiliar:
        matriz matrizAuxiliar(3,4);

        matrizAuxiliar(0,0) = 1.0;
        matrizAuxiliar(1,3) = 1.0;
        matrizAuxiliar(2,1) = 1.0;
        matrizAuxiliar(2,2) = 1.0;

        // Inicialização da matriz cinemática com o produto triplo:
        auto matrizCinematica = matrizAuxiliar * matrizH * matrizDeDeformacao;


        return std::move(matrizCinematica);
    }

    // Inserção da matriz constitutiva do elemento, presente no cálculo
    // da integração de Gauss:
    void MatrizConstitutiva() {

        // Inicialiação da constante de multiplicação
        T constante = material->ModuloElasticidade()/((1.0 + material->CoeficientePoisson()) *
                      (1.0 - (2.0 * material->CoeficientePoisson())));

        matrizConstitutiva(0,0) = constante * (1.0 - material->CoeficientePoisson());
        matrizConstitutiva(0,1) = constante * (material->CoeficientePoisson());
        matrizConstitutiva(1,0) = constante * (material->CoeficientePoisson());
        matrizConstitutiva(1,1) = constante * (1.0 - material->CoeficientePoisson());
        matrizConstitutiva(2,2) = constante * (1.0 - ((2.0 * material->CoeficientePoisson())/2.0));
    }

public:

    // Construtor:
    QuadrilateroIsoparametrico(ptr_face &coordenadasGeometricas,
                                ptr_material &material, const T espessura)
                               : nosDoElemento(coordenadasGeometricas),
                                 material(material),
                                 matrizConstitutiva(3,3),
                                 espessura(espessura)
                                 {MatrizConstitutiva();}

    // Destrutor:
    ~QuadrilateroIsoparametrico () {}

    // Retorna a dimensão do espaço em que se encontra o elemento,
    // no caso, 2.

    int Dimensao() const {return dimensao;}

    // Inserção do produto triplo da integração de gauss, com a inicialização
    // dos elementos do produto, a inicialização dos três pontos é necessária
    // para a implementação da função na integracao:

    matriz_sim ProdutoTriplo(const T pontoX = 0.0, const T pontoY = 0.0
                                                 , const T PontoZ = 0.0) const {

        auto matrizJacobiana = MatrizJacobiana(pontoX, pontoY);
        auto determinanteJacobiano = DeterminanteMatrizJacobiana(matrizJacobiana);
        auto matrizJacobianaInversa = MatrizJacobianaInversa(matrizJacobiana, determinanteJacobiano);

        auto matrizCinematica = MatrizCinematica(pontoX, pontoY, matrizJacobianaInversa);

        return MultiplicacaoTripla(matrizCinematica, matrizConstitutiva, determinanteJacobiano * espessura);
    }

    // Cálculo da matriz de rigidez elementar pela integração
    // numérica de Gauss.
    auto MatrizRigidezElementar() const  {

        // Número de pontos usados para a intregração no polinômio:
        int numeroDePontos = 2;

        // Integração numérica segundo a quadradatura de Gauss:

        matriz_sim matrizRigidezElementar = integracao::Integral(*this, numeroDePontos);

        return std::move(matrizRigidezElementar);
    }

    auto GetCoordenada() const {

        // Retorna o vetor contendo as coordenadas das faces do elemento, colocando-as
        // em um vetor para melhor acesso.

        std::vector<FEM::No<FEM::Ponto2D, T> > vetor;

        typename ptrLista::const_iterador it;

        for(it = nosDoElemento->GetPontos().begin(); it != nosDoElemento->GetPontos().end(); it++) {
            vetor.push_back(*it);
        }

        return std::move(vetor);
    }

};

}
#endif
