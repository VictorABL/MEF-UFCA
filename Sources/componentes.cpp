#include <vector>

// Estruturas básicas de dimensões dos elementos, no caso,
// a definição das coordenadas e do menor elemento unitário,
// um nó da estrutura.


namespace FEM {

template<class Tipo = double>
class Ponto2D {

    // Define um objeto ponto de um sistema de coordenadas qualquer bidimensional.

private:
    // Atributo que contem as coordenadas do ponto.
    std::vector<Tipo> coordenadas;

public:

    // Construtor:
    Ponto2D(const std::vector<Tipo> &coordenadas): coordenadas(coordenadas) {}

    // Destrutor:
    ~Ponto2D() {}

    // Função que retorna o vetor de coordenadas do ponto.
    std::vector<Tipo> &GetCoordenada() {return coordenadas;}

    // Para instanciações constantes:
    const std::vector<Tipo> &GetCoordenada() const {return coordenadas;}

};

template<class Tipo = double>
class Ponto3D {

    // Define um objeto ponto de um sistema de coordenadas qualquer bidimensional.

private:

    // Vetor que contem as coordenadas do ponto.
    std::vector<Tipo> coordenadas;

public:

    // Construtor:
    Ponto3D(const std::vector<Tipo> &coordenadas): coordenadas(coordenadas) {}

    // Destrutor:
    ~Ponto3D() {}

    // Retorna o vetor de dimensões do ponto.
    std::vector<Tipo> &GetCoordenada() {return coordenadas;}

    // Para isntanciações constantes:
    const std::vector<Tipo> &GetCoordenada() const {return coordenadas;}


};

// Classe de definição dos graus de liberdade da estrutura.
template<class Tipo>
class GrausDeLiberdade {
private:

    // Define o vetor de numeração dos graus de liberdade.
    std::vector<Tipo> grausDeLiberdade;
    size_t numeroDeGrausDeLiberdade;
    // Define o contador para os graus livres, como é um atributo
    // que é definido para toda a estrutura, independe de qualquer
    // instanciação, é estático.
    static int numeroDoGrauLivre;

public:

    // Construtor:
    GrausDeLiberdade(size_t numeroDeGrausDeLiberdade): grausDeLiberdade(numeroDeGrausDeLiberdade),
    numeroDeGrausDeLiberdade(numeroDeGrausDeLiberdade) {}

    // Destrutor:
    ~GrausDeLiberdade() {};

    // Função que enumera os graus de liberade com base no atual
    // contador dos graus de toda a estrutura.
    void EnumerarGrausDeLiberdade() {

        for(size_t iterador = 0; iterador < grausDeLiberdade.size(); iterador++ ) {
            if (grausDeLiberdade[iterador] >= 0) {
                grausDeLiberdade[iterador] = numeroDoGrauLivre;
                numeroDoGrauLivre++;
        }
    }

}
    // usada para a restrição será o inteiro -1
    void RestringirGrausDeLiberdade(const std::vector<Tipo> &vetorDeRestricao) {
        // Função que restringe o grau de elemento, a notação
        for(size_t iterador = 0; iterador < grausDeLiberdade.size(); iterador++)
            grausDeLiberdade[vetorDeRestricao[iterador]] = -1;
    }

    // Retorna o vetor de graus de liberdade.
    const std::vector<Tipo> &GetGrausDeLiberdade() const {return grausDeLiberdade;}

};

// Definição da variável estática numeroDoGrauLivre
// **precisa de implementação no header file (fazer alteração)....
template<class T>
int FEM::GrausDeLiberdade<T>::numeroDoGrauLivre = 0;

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
    No(const Estrutura<Tipo> &vetorEntrada, size_t numeroDeGrausDeLiberdade = 0):
    dimensao(vetorEntrada), vetorGrausDeLiberdade(numeroDeGrausDeLiberdade) {}

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
