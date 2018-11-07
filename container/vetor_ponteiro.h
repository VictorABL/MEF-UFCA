

#ifndef VETOR_PONTEIRO_H
#define VETOR_PONTEIRO_H

#include <vector>
#include<memory>
#include <boost/iterator/indirect_iterator.hpp>

namespace FEM {

template<class TipoDeDado,
         class Ponteiro = std::shared_ptr<TipoDeDado>,
         class Estrutura = std::vector<Ponteiro> >

class VetorPonteiro {

    // Implementação de um container de ponteiros da forma shared_ptr com base na STL e na biblioteca Kratos,
    // a classe não é especializada em utilizar todas as funções de um container como o vector,
    // apenas algumas funções específicas para implementação no programa.

public:

    typedef boost::indirect_iterator<typename Estrutura::iterator> iterador;

    typedef boost::indirect_iterator<typename Estrutura::const_iterator> const_iterador;


    using Tipo = TipoDeDado;

private:

    // Container que irá conter os shared_ptr:
    Estrutura container;

public:

    // Contrutores:
    // Padrão:
    VetorPonteiro (): container() {}

    // De cópia:
    VetorPonteiro (const VetorPonteiro<Tipo> &vetor_ponteiro)
    : container(vetor_ponteiro.GetContainer()) {}

    // Com inicialização do vetor:
    explicit VetorPonteiro (const int tamanho): container(tamanho) {}

    // Destrutor:
    ~VetorPonteiro() {}

    // Retorno do container:
    Estrutura &GetContainer() {return container;}

    // Para elementos contantes:
    const Estrutura &GetContainer() const {return container;}

    // Indexação dos elementos:
    Tipo &operator[] (const int posicao) {return *(container[posicao]);}

    // Para elementos constantes:
    const Tipo &operator[] (const int posicao) const {return *(container[posicao]);}

    // Indexação dos endereços dos elementos:
    Ponteiro operator() (const int posicao) {return container[posicao];}

    // Para elementos constantes:
    const Ponteiro operator() (const int posicao) const {return container[posicao];}


    // Adiciona uma referência ao elemento no final do vetor, pois shared_ptr mantém o destino:
    void Adicionar(Ponteiro ponteiro) {container.push_back(ponteiro);}

    // Remove o último elemento:
    void Remover() {container.pop_back();}

    // Iteradores:
    iterador begin() {return iterador(container.begin());}
    iterador end() {return iterador(container.end());}

    // Constantes:
    const_iterador begin() const {return const_iterador(container.begin());}
    const_iterador end() const {return const_iterador(container.end());}

    // Tamanho do container:
    auto Tamanho() {return container.size();}

    void Trocar(VetorPonteiro &ponteiro_vetor) {container.swap(ponteiro_vetor.GetContainer());}

};
}

#endif
