
#ifndef NO_H
#define NO_H

#include "dois_d.h"
#include "tres_d.h"
#include "graus.h"

namespace FEM {

template<template<class T> class Estrutura, class Tipo = double>
class No {
private:

    // Define a estrutura do ponto, ou seja, suas dimensões pondendo ser
    // 3D ou 2D.

    Estrutura<Tipo> dimensao;
    // Define o vetor de graus de liberdade da estrutura.
    GrausDeLiberdade<int> vetorGrausDeLiberdade;

public:

    // Contrutor:
    No(const Estrutura<Tipo> &vetorEntrada, size_t numeroDeGrausDeLiberdade = 0)
    : dimensao(vetorEntrada),
      vetorGrausDeLiberdade(numeroDeGrausDeLiberdade) {}

    // Destrutor:
    ~No() {}

    // Retorna o vetor de coordenadas espaciais do nó.
    std::vector<Tipo> &GetCoordenadas() {return (dimensao.GetCoordenada());}

    // Para instacianções constantes:
    const std::vector<Tipo> &GetCoordenadas() const {return dimensao.GetCoordenada();}


    // Função que enumera os graus de liberdade.
    void EnumeraGrausDeLiberdade() {vetorGrausDeLiberdade.EnumerarGrausDeLiberdade();}

    // Retorna o vetor de graus de liberdade.
    auto GetVetorGrausDeLiberdade() -> decltype(vetorGrausDeLiberdade.GetGrausDeLiberdade()) const
    {return vetorGrausDeLiberdade.GetGrausDeLiberdade();}

    // Restringe os graus de liberdade do nó pelo devido vetor.
    void RestringirGraus(const std::vector<int> &vetorDeRestricao) {
        vetorGrausDeLiberdade.RestringirGrausDeLiberdade(vetorDeRestricao);
    }
};
}

#endif
