#include "Lista.h"

Lista::Lista() : prim(nullptr), ult(nullptr){};

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();

}

Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);

    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem, nullptr, nullptr);
    if (prim == nullptr){
        prim=nuevo;
        ult=nuevo;
    } else {
        nuevo -> sig = prim;
        (nuevo -> sig) -> prev = nuevo;
        prim = nuevo;
    }

}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem, nullptr, nullptr);
    if (prim == nullptr){
        prim=nuevo;
        ult=nuevo;
    } else {
        nuevo -> prev = ult;
        (nuevo -> prev) -> sig = nuevo;
        ult = nuevo;
    }

}

void Lista::eliminar(Nat i) {
    int iteracion = 0;
    Nodo* actual = prim;
    while (iteracion != i){
        iteracion++;
        actual = actual -> sig;
    }
    Nodo* antes = actual->prev;
    Nodo* despues = actual->sig;
    delete actual;

    if(antes == nullptr){
        prim = despues;
    } else {
        antes -> sig = despues;
    }

    if(despues == nullptr){
        ult = antes;
    } else {
        despues -> prev = antes;
    }


}

int Lista::longitud() const {
    Nodo* actual = prim;
    int contador = 0;
    while (actual != nullptr){
        contador++;
        actual = actual->sig;
    }

    return contador;
}

const int& Lista::iesimo(Nat i) const {

    Nodo* actual = prim;
    for (int j=0; j<i; j++){
        actual = actual -> sig;
    }
    return actual->valor;
}


int& Lista::iesimo(Nat i) {
    int iteracion = 0;
    Nodo* actual = prim;
    while(iteracion != i){
        iteracion++;
        actual = actual->sig;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    Nodo* actual = prim;
    o << "Lista: ";
    while(actual != nullptr){
        o << actual->valor << ' ';
        actual = actual->sig;
    }
    o << endl;
}


void Lista::copiarNodos(const Lista &o) {
    Nodo* actual = o.prim;
    while(actual!= nullptr){
        agregarAtras(actual->valor);
        actual = actual -> sig;
    }

}

void Lista::destruirNodos() {
    Nodo* actual = prim;
    while (actual != nullptr){
        Nodo* siguiente = actual-> sig;
        delete actual;
        actual = siguiente;
    }
    prim = nullptr;
}
