
#ifndef MEF_UFCA_TRES_D_H
#define MEF_UFCA_TRES_D_H

namespace FEM {

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
