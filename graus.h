
#ifndef GRAUS_H
#define GRAUS_H

// Classe de definição dos graus de liberdade da estrutura.
namespace FEM {

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
    GrausDeLiberdade(size_t numeroDeGrausDeLiberdade)
                    : grausDeLiberdade(numeroDeGrausDeLiberdade),
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

template<class T>
int FEM::GrausDeLiberdade<T>::numeroDoGrauLivre = 0;

}

#endif
