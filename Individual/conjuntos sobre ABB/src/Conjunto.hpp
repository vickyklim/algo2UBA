
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr) {}

template <class T>
void Conjunto<T>::destruirNodos(Nodo* n) {
    if(n != nullptr){
        destruirNodos(n->izq);
        destruirNodos(n->der);
        delete n;
    }
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodos(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* n = _raiz;
    while(n!= nullptr){
        if(n->valor == clave){
            return true;
        }
        if(clave < n->valor){
            n = n->izq;
        } else {
            n = n->der;
        }
    } return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (not pertenece(clave)){
        if (_raiz == nullptr) {
            _raiz = new Nodo(clave);
        } else {
            Nodo *n = _raiz;
            while (clave != n->valor) {
                if (clave < n->valor) {
                    if (n->izq == nullptr) {
                        n->izq = new Nodo(clave);
                    }
                    n = n->izq;
                } else if (clave > n->valor){
                    if (n->der == nullptr) {
                        n->der = new Nodo(clave);
                    }
                    n = n->der;
                } else {
                    break;
                }
            }
        }
    }
}

/*
template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::insertarTodos(Nodo* n) {
    if(n!=nullptr){
        insertar(n->valor);
        insertarTodos(n->izq);
        insertarTodos(n->der);
    }
}
*/

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscarNodoPadre(const T& clave) {
    Nodo *n = _raiz;
    Nodo *padre = _raiz;
    while (n->valor != clave) {
        if (clave < n->valor) {
            padre = n;
            n = n->izq;
        } else {
            padre = n;
            n = n->der;
        }
    } return padre;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::siguienteNodo(const T& clave) {
    assert(pertenece(clave));

    //busco el nodo
    Nodo *n = _raiz;
    Nodo *antecesorMasGrande = _raiz;
    Nodo *hijoSgte;
    while (n->valor != clave) {
        if (clave < n->valor) {
            antecesorMasGrande = n;
            n = n->izq;
        } else {
            n = n->der;
        }
    }
    if (n->der == nullptr) {
        return antecesorMasGrande;
    } else {
        hijoSgte = n->der;
        while (hijoSgte->izq != nullptr) {
            hijoSgte = hijoSgte->izq;
        }
    }
    if (antecesorMasGrande->valor < clave) {
        return hijoSgte;
    } else if (antecesorMasGrande->valor != clave and antecesorMasGrande->valor < hijoSgte->valor) {
        return antecesorMasGrande;
    } else {
        return hijoSgte;
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {
    assert(pertenece(clave));
    //busco el nodo
    Nodo *n = _raiz;
    Nodo *padre = _raiz;
    while (n->valor != clave) {
        if (clave < n->valor) {
            padre = n;
            n = n->izq;
        } else {
            padre = n;
            n = n->der;
        }
    }
    if (n == padre and n->der == nullptr) { //raiz, sin hijo derecho
        _raiz = n->izq;
        delete n;

    } else if (n == padre) { //raiz, con hijo derecho
        Nodo *futuraRaiz = siguienteNodo(n->valor);
        Nodo *padreFuturaRaiz = buscarNodoPadre(futuraRaiz->valor);
        n->valor = futuraRaiz->valor;
        if(n->der == futuraRaiz){ //el siguiente es hijo inmediato
            n->der = futuraRaiz->der;
        } else {
            padreFuturaRaiz->izq = futuraRaiz->der;
        } delete futuraRaiz;


    } else if (padre->der == n && n->der == nullptr) { //sin hijo derecho, padre por derecha
        padre->der = n->izq;
        delete n;

    } else if (padre->der==n) { //padre por derecha
        Nodo *nuevo = siguienteNodo(n->valor);
        Nodo *padreNuevo = buscarNodoPadre(nuevo->valor);
        if(n->der == nuevo) { //el siguiente es hijo inmediato
            padre->der = nuevo;
            nuevo->izq = n->izq;
            delete n;
        }else{
            n->valor = nuevo->valor;
            padreNuevo->izq = nuevo->der;
            delete nuevo;
        }

    } else if (padre->izq == n && n->der == nullptr) { //sin hijo derecho, padre por izquierda
        padre->izq = n->izq;
        delete n;

    } else if (padre->izq==n) { // padre por izquierda
        Nodo *nuevo = siguienteNodo(n->valor);
        Nodo *padreNuevo = buscarNodoPadre(nuevo->valor);
        if (n->der == nuevo) { //el siguiente es hijo inmediato
            padre->izq = nuevo;
            nuevo->izq = n->izq;
            delete n;
        } else {
            n->valor = nuevo->valor;
            padreNuevo->izq = nuevo->der;
            delete nuevo;
        }
    }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(pertenece(clave));
    return siguienteNodo(clave)->valor;
}


template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo *n = _raiz;
    while(n->izq != nullptr){
        n=n->izq;
    }
    return n->valor;
}


template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo *n = _raiz;
    while(n->der != nullptr){
        n=n->der;
    }
    return n->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinalAux(Nodo* n) const {
    unsigned int res = 0;
    if(n != nullptr){
        res = 1 + cardinalAux(n->izq) + cardinalAux(n->der);
    }
    return res;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalAux(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    Nodo* actual = minimo();
    Nodo* ult = maximo();
    if(actual != ult){
        o << "Conjunto: ";
        while(actual != ult){
            o << actual->valor << ' ';
            actual = siguienteNodo(actual->valor);
        }
        o << ult->valor << ' ' << endl;
    } else {
        o << "Conjunto: " << actual->valor << ' ' << endl;
    }
}