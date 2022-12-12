#include "ConjTrie.h"



ConjTrie::ConjTrie(){
    raiz_ = nullptr;
    altura_ = 0;
}

void ConjTrie::agregarPalabras(set<Palabra> pl) {
    if(raiz_ == nullptr){
        raiz_ = new Nodo();
    }
    for(Palabra p:pl){
        Nodo* actual = raiz_;
        for(Letra l:p){
            if(actual->hijos[ord(l)]== nullptr) {
                Nodo* n = new Nodo();
                actual->hijos[ord(l)] = n;
                actual = actual->hijos[ord(l)];
            } else {
                actual = actual->hijos[ord(l)];
            }
        }
        actual->flag = true;
        if(p.size()>altura_){
            altura_=p.size();
        }
    }
}


bool ConjTrie::pertenece(Palabra p) const{
    if(raiz_ == nullptr){
        return false;
    }
    Nodo* actual = raiz_;
    for(int i=0; i<p.size(); i++){
        if (actual->hijos[ord(p[i])]==nullptr){
            return false;
        } else {
            actual = actual->hijos[ord(p[i])];
        }
    }
    return actual->flag;
}

Nat ConjTrie::altura() const {
    return altura_;
}


ConjTrie::~ConjTrie() {
    if(raiz_!= nullptr) {
        destruirNodos(raiz_);
    }
}


void ConjTrie::destruirNodos(ConjTrie::Nodo* n) {
    if (n != nullptr) {
        for (int i = 0; i < TAMANIO_ALFABETO; i++) {
            destruirNodos(n->hijos[i]);
        }
        delete n;
    }
}





/*ConjTrie::ConjTrie(const ConjTrie &otro) {
    raiz_=new Nodo;
    raiz_=asignarNodos(otro.raiz_);
}

bool ConjTrie::tieneHijos(ConjTrie::Nodo *a) {
    for (int i = 0; i < 256; i++) {
        if(a->hijos[i]!= nullptr){
            return true;
        }
    }
    return false;
}

ConjTrie::Nodo *ConjTrie::asignarNodos(ConjTrie::Nodo *otro) {
    Nodo* copia;
    copia->flag=otro->flag;
    if(tieneHijos(otro)){
        for (int i = 0; i < 256; i++) {
            copia->hijos[i]= asignarNodos(otro->hijos[i]);
        }
    } else {
        copia=otro;
    }
    return copia;
}*/

ConjTrie::ConjTrie(const ConjTrie &otro) {
    if (otro.raiz_!= nullptr){
        raiz_=new Nodo;
        asignarNodos(raiz_, otro.raiz_);
    }
}

void ConjTrie::asignarNodos(ConjTrie::Nodo *a, ConjTrie::Nodo *otro) {
    a->flag=otro->flag;
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        if(otro->hijos[i]!= nullptr){
            a->hijos[i]=new Nodo;
            asignarNodos(a->hijos[i], otro->hijos[i]);
        }
    }
}






