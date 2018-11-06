
#ifndef ANALISE_H
#define ANALISE_H

#include "malha.h"

namespace FEM {

template<template<template<class A> class B, class C> class Elemento,
         template<class E> class Material,
         template<class D> class Dimensao, class Tipo = double>
class Analise {

    // Classe de processamento do programa, é nela que serão feitas as análises e os
    // cálculos para a resolução dos parâmetros definidos de toda a estrutura.

public:


    typedef typename FEM::ListaPonteiro<Elemento<Material, Tipo> > ptrLista_elementos;
    typedef typename FEM::ListaPonteiro<FEM::Face<Dimensao, Tipo> > ptrLista_faces;
    typedef typename FEM::VetorPonteiro<FEM::No<Dimensao, Tipo> > ptrVetor_pontos;
    typedef typename FEM::ListaPonteiro<FEM::Apoio<Dimensao, Tipo> > ptrLista_apoios;
    typedef typename FEM::ListaPonteiro<Material<Tipo> > ptrLista_materiais;

    typedef typename FEM::Malha<Elemento, Material, Dimensao, Tipo> ref_malha;

    typedef typename std::shared_ptr< FEM::No<Dimensao, Tipo> > shared_ptr_no;
    typedef typename std::shared_ptr< FEM::Apoio<Dimensao, Tipo> > shared_ptr_apoio;


    using vetor_int = std::vector<int>;

private:


    // Tamanho da malha;
    Tipo tamanho;
    // Material da malha.
    Material<Tipo> material;
    // Espessura da malha.
    Tipo espessura;
    // Define o número de graus de liberdade para a estrutura:
    int grausDeLiberdade;

    // Objeto contendo uma malha:
    ref_malha malha;

    // Lista e vetores com os elementos da malha:
    ptrLista_elementos listaElementos;
    ptrVetor_pontos vetorPontos;
    ptrLista_apoios listaApoios;
    // listaCarregamentos;
    ptrLista_materiais listaMateriais;



    // Cria uma malha com base nos parâmetros associados:
    void Desenhar() {malha = ref_malha(tamanho, material, espessura, grausDeLiberdade);}
    // Adiciona o vetor de nós da malha à classe:
    void AdicionaNo() {vetorPontos = malha.GetPontos();}

    void AdicionaElementos() {listaElementos = malha.GetElementos();}

public:

    // Constutor:
    Analise (const Tipo tamanho, const Material<Tipo> &material,
              const Tipo espessura, const int grausDeLiberdade)

            : tamanho(tamanho),
              material(material),
              espessura(espessura),
              grausDeLiberdade(grausDeLiberdade),
              listaElementos() ,vetorPontos() ,listaApoios() {}

    // Destrutor:
    ~Analise () {}

    void CriarMalha() {

        Desenhar();
        AdicionaNo();
        AdicionaElementos();
    }


    void AdicionarApoio( int indexador, const vetor_int &restricao) {

        // Cria um objeto apoio com a referência ao nó indicado pelo indexador:
        shared_ptr_apoio apoio(new FEM::Apoio<Dimensao, Tipo>(vetorPontos(indexador), restricao));

        // Adiciona à lista de apoios da estrutura:
        listaApoios.AdicionarFinal(apoio);
    }


    // Função de enumeração dos graus de liberdade da estrutura:
    void EnumerarGraus() {

        // Iterador:
        typename ptrVetor_pontos::iterador it;

        // Enumeração:
        for(it = vetorPontos.begin(); it != vetorPontos.end(); it++) {
            it->EnumeraGrausDeLiberdade();
        }



    }

    void ImprimirGraus () {

        // Iterador:
        typename ptrVetor_pontos::iterador it;

        for(it = vetorPontos.begin(); it != vetorPontos.end(); it++) {
            auto vetor = it->GetVetorGrausDeLiberdade();
            for(int i = 0; i < vetor.size(); i++)
            std::cout << vetor[i] << '\n';
        }
    }

    // Retorno da malha:
    ref_malha &GetMalha() {return malha;}

    ptrLista_elementos &GetElementos() {return listaElementos;}
};

}
#endif