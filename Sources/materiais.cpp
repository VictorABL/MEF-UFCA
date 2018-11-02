
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
    T moduloElasticidade, coeficientePoisson, espessura;

public:

    // Construtor:
    Material (std::string nome, T moduloElasticidade, T coeficientePoisson, T espessura):
    nome(nome), moduloElasticidade(moduloElasticidade),
    coeficientePoisson(coeficientePoisson), espessura(espessura) {}

    // Destrutor:
    ~Material () {}

    // Getters:
    const T ModuloElasticidade() const {return moduloElasticidade;}
    const T CoeficientePoisson() const {return coeficientePoisson;}
    const T Espessura() const {return espessura;}

};

}
