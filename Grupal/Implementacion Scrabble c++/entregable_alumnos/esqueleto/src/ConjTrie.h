#ifndef TP_JUEGODEPALABRAS_CONJTRIE_H
#define TP_JUEGODEPALABRAS_CONJTRIE_H



#include "Letra.h"

//Trie de palabras legitimas.

class ConjTrie{
public:
    ConjTrie();
    ConjTrie(const ConjTrie& otro);
    void agregarPalabras(set<Palabra>);
    bool pertenece(Palabra p) const;
    Nat altura() const;
    ~ConjTrie();




private:
    struct Nodo{
        bool flag;
        vector<Nodo*> hijos;
        Nodo(){
            flag = false;
            hijos = vector<Nodo*>(TAMANIO_ALFABETO, nullptr);
        }
    };
    Nodo* raiz_;
    Nat altura_;
    void destruirNodos(Nodo*);
    void asignarNodos(Nodo* a, Nodo* otro);
    bool tieneHijos(Nodo* a);
};


#endif //TP_JUEGODEPALABRAS_CONJTRIE_H