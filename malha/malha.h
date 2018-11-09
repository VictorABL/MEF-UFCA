
#ifndef MALHA_H
#define MALHA_H

#include <memory>
#include <math.h>
#include <boost/ptr_container/ptr_vector.hpp>

#include "face.h"
#include "dois_d.h"
#include "tres_d.h"
#include "lista_ponteiro.h"
#include "vetor_ponteiro.h"

namespace FEM {

template<template<template<class A> class B, class C> class Elemento,
         template<class D> class Material,
         template<class E> class Dimensao,class Tipo = double>
class Malha {

public:

    typedef typename FEM::ListaPonteiro<Elemento<Material, Tipo> > ptrLista_elementos;

    typedef typename FEM::ListaPonteiro<FEM::Face<Dimensao, Tipo> > ptrLista_faces;

    typedef typename FEM::ListaPonteiro<FEM::No<Dimensao, Tipo> > ptrLista_pontos;

    typedef typename FEM::VetorPonteiro<FEM::No<Dimensao, Tipo> > ptrVetor_pontos;


    typedef typename std::shared_ptr<Elemento<Material, Tipo> > shared_ptr_elementos;

    typedef typename std::shared_ptr<FEM::Face<Dimensao, Tipo> > shared_ptr_face;

    typedef typename std::shared_ptr<FEM::No<Dimensao, Tipo> > shared_ptr_pontos;

    typedef typename std::shared_ptr< Material<Tipo> > shared_ptr_material;


    using ptr_face = typename FEM::Face<Dimensao, Tipo>;

private:


    // Implementação da estrutura da malha do programa, bidimensional,
    // quadrada, com elementos quadrados de dimensão iguais
    // a 2, com início na origem do sistema cartesiano.

    // Comprimento da malha.
    int comprimento;
    // Material da malha.
    shared_ptr_material material;
    // Espessura.
    Tipo espessura;
    // Graus de liberdade do nó da malha.
    int grausDeLiberdade;

    // Lista contendo os pontos da malha.
    ptrVetor_pontos pontos;
    // Lista contendo as faces da malha.
    ptrLista_faces faces;
    // Lista contendo os elementos da malha.
    ptrLista_elementos elementos;
    // Distância entre os pontos.
    static int distancia;


    // #################################################################################################################
    // #################################################################################################################


    void CriarPontos() {

        // Função de geração dos pontos da malha:
        for(double vertical = 0; vertical <= comprimento; vertical += distancia) {
            for(double horizontal = 0; horizontal <= comprimento; horizontal += distancia) {

                Dimensao<Tipo> ponto({horizontal, vertical});
                shared_ptr_pontos ponteiro(new FEM::No<Dimensao, Tipo>(ponto, grausDeLiberdade));
                pontos.Adicionar(ponteiro);
            }
        }
    }

    void CriarElementos() {

        // Número de pontos em cada linha da malha:
        size_t ptsPorLinha = (comprimento / distancia) + 1;

        // Ponto limite para a geração das faces:
        size_t limite = pow(ptsPorLinha, 2) - ptsPorLinha;

        for(size_t linha = 0; linha < limite; linha += ptsPorLinha) {
            for(size_t vez = linha; vez < linha + ptsPorLinha - 1; vez++) {

                // Criação da lista de pontos a ser adicionada na face:
                ptrLista_pontos lista;

                lista.AdicionarFinal(pontos(vez));
                lista.AdicionarFinal(pontos(vez + 1));
                lista.AdicionarFinal(pontos(vez + ptsPorLinha + 1));
                lista.AdicionarFinal(pontos(vez + ptsPorLinha));

                // Criação da face:
                shared_ptr_face face(new ptr_face(lista));

                // Adição da face à lista de faces da malha:
                faces.AdicionarFinal(face);

                // Criação dos elementos da malha:
                shared_ptr_elementos elemento(new Elemento<Material, Tipo>(face, material, espessura));
                elementos.AdicionarFinal(elemento);
            }
        }
    }

    void Gerar() {

        // Função de geração da malha, criandos os pontos
        // e as faces:

        CriarPontos();
        CriarElementos();
    }

public:

    // Construtor:
    // Padrão:
    Malha(): comprimento(), material(), espessura(), grausDeLiberdade() {}

    Malha(const int comprimento, shared_ptr_material &material,
               const Tipo espessura, const int grausDeLiberdade)

          : comprimento(comprimento),
            material(material),
            espessura(espessura),
            grausDeLiberdade(grausDeLiberdade) {Gerar();}

    // Destrutor:
    ~Malha () {}


    // Retorna o vetor de pontos:
    ptrVetor_pontos &GetPontos() {return pontos;}

    // Para instanciações constantes:
    const ptrVetor_pontos &GetPontos() const {return pontos;}

    // Retorna a lista de faces:
    ptrLista_faces &GetFaces() {return faces;}

    // Para instanciações constantes:
    const ptrLista_faces &GetFaces() const {return faces;}

    // Retorna a lista de elementos:
    ptrLista_elementos &GetElementos() {return elementos;}

    // Para instanciações constantes:
    const ptrLista_elementos &GetElementos() const {return elementos;}

};

template<template<template<class A> class B, class C> class Elemento,
         template<class D> class Material,
         template<class E> class Dimensao, class Tipo>
int FEM::Malha<Elemento, Material, Dimensao, Tipo>::distancia = 2;

}

#endif
