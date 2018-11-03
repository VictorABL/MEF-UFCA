
#ifndef PONTO_H
#define PONTO_H

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
}

#endif
