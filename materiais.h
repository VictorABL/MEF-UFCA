
#ifndef MATERIAIS_H
#define MATERIAIS_H


#include <iostream>
#include <vector>
#include <string>


// Classe de inplementação das caracteristicas
// físicas do elemento:

namespace FEM {

template<class T = double>
class Material {
private:

    // Componentes e características dos materiais:
    std::string nome;
    T moduloElasticidade, coeficientePoisson;

public:

    // Construtor:
    Material (std::string nome, T moduloElasticidade, T coeficientePoisson):
    nome(nome), moduloElasticidade(moduloElasticidade),
    coeficientePoisson(coeficientePoisson) {}

    // Destrutor:
    ~Material () {}

    // Getters:
    const T ModuloElasticidade() const {return moduloElasticidade;}
    const T CoeficientePoisson() const {return coeficientePoisson;}

};

}

#endif
