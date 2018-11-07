

#ifndef LISTA_PONTEIRO_H
#define LISTA_PONTEIRO_H

#include <list>
#include <boost/iterator/indirect_iterator.hpp>

namespace FEM {

template<class TipoDeDado,
         class Ponteiro = std::shared_ptr<TipoDeDado>,
         class Estrutura = std::list<Ponteiro> >
class ListaPonteiro {

    // Implementação de uma lista de ponteiros, da forma shared_ptr baseada na STL,
    // a classe não é especializada para utilizar todas as funções de uma lista, apenas
    // as que serão utilizadas no programa.

public:

    typedef boost::indirect_iterator<typename Estrutura::iterator> iterador;

    typedef boost::indirect_iterator<typename Estrutura::const_iterator> const_iterador;


    typedef typename Estrutura::iterator ptr_iterador;

    typedef typename Estrutura::const_iterator ptr_const_iterador;


    using Tipo = TipoDeDado;

private:

    // Container para alocação dos ponteiros:
    Estrutura container;

public:

    // Construtores:
    // Padrão:
    ListaPonteiro (): container() {}

    // De cópia:
    ListaPonteiro (const ListaPonteiro<Tipo> &ponteiro_lista): container(ponteiro_lista.GetContainer()) {}

    // Destrutor:
    ~ListaPonteiro () {}

    // Retorno da lista completa:
    Estrutura &GetContainer() {return container;}

    // Para isntanciações constantes:
    const Estrutura &GetContainer() const {return container;}

    // Adiciona um elemento ao final da lista:
    void AdicionarFinal(Ponteiro ponteiro) {container.push_back(ponteiro);}

    // Adinciona um elemento no início da lista:
    void AdicionarInicio(Ponteiro ponteiro) {container.push_front(ponteiro);}

    // Remove o último elemento:
    void RemoverUltimo() {container.pop_back();}

    // Remove o último elemento:
    void RemoverPrimeiro() {container.pop_front();}

    // Iteradores:
    iterador begin() {return iterador(container.begin());}
    iterador end() {return iterador(container.end());}

    // Constantes:
    const_iterador begin() const {return const_iterador(container.begin());}
    const_iterador end() const {return const_iterador(container.end());}

    // Tamanho do container:
    auto Tamanho() {return container.size();}

    void Trocar(ListaPonteiro &ponteiro_lista) {container.swap(ponteiro_lista.GetContainer());}

    // Verifica se a lista possui elementos:
    bool Vazio() const {return container.empty();}

};
}

#endif
