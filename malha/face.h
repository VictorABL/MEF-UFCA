
#ifndef FACE_H
#define FACE_H

#include "lista_ponteiro.h"
#include "vetor_ponteiro.h"
#include "dois_d.h"
#include "tres_d.h"
#include "no.h"

namespace FEM {

template<template<class B> class Estrutura, class Tipo = double>
class Face {

    // Implementação da classe das faces da malha, que darão origem
    // à criação dos elementos da malha.

public:

    typedef typename FEM::ListaPonteiro<FEM::No<Estrutura,Tipo> > ptrLista;

    typedef typename FEM::VetorPonteiro<FEM::No<Estrutura,Tipo> > ptrVetor;

private:

    // Container de nós da face:
    ptrLista pontos;

public:

    // Construtores:
    // Padrão:
    Face () {}

    // Sobrecarregado com lista adicionado:
    Face (const ptrLista &pontos): pontos(pontos) {}

    // Destrutor:
    ~Face () {}

    // Retorna a referência aos pontos:
    ptrLista &GetPontos () {return pontos;}

    // Para instanciações contantes:
    const ptrLista &GetPontos () const {return pontos;}

};

}

#endif
