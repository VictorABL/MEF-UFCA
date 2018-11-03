#ifndef APOIO_H
#define APOIO_H

#include "no.h"
#include "graus.h"

namespace FEM {

template<template<class B> class Estrutura, class Tipo = double>
class Apoio {

    // Implementação da classe apoio, referencia os nós
    // com graus impedidos.
private:

    // Ponteiro para o nó impedido:
    // Vetor dos graus impedidos:
    // FEM::No<Estrutura, Tipo> *nos;

    std::shared_ptr< FEM::No<Estrutura, Tipo> > ponteiro;
    std::vector<int> apoios;

public:

    // Construtor:
    Apoio(FEM::No<Estrutura, Tipo> &nos, const std::vector<int> &apoio)
          : ponteiro(&nos),
            apoios(apoio)
            {RestringirNo();}

    // Destrutor:
    ~Apoio () {}

private:

    // Função de restrição do nó:
    void RestringirNo() {ponteiro->RestringirGraus(apoios);}

};
}

#endif
