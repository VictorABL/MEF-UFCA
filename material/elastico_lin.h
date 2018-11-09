
#ifndef MEF_UFCA_ELASTICO_LIN_H
#define MEF_UFCA_ELASTICO_LIN_H

#include <vector>
#include <string>


// Classe de inplementação das caracteristicas
// físicas do elemento:

namespace FEM {

template<class T = double>
class LinearElastico {
private:

    // Componentes e características dos materiais:
    std::string nome;
    T moduloElasticidade, coeficientePoisson;

public:

    // Construtor:
    // Padrão:
    LinearElastico ()
                    : nome(),
                      moduloElasticidade(),
                      coeficientePoisson() {}

    // Sobrecarregado com os parâmetros:
    LinearElastico (const std::string nome, const T moduloElasticidade,
                                            const T coeficientePoisson)
                   :nome(nome),
                    moduloElasticidade(moduloElasticidade),
                    coeficientePoisson(coeficientePoisson) {}

    // Destrutor:
    ~LinearElastico () {}

    // Getters:
    const T ModuloElasticidade() const {return moduloElasticidade;}
    const T CoeficientePoisson() const {return coeficientePoisson;}

};

}

#endif
