
#include "string_map.h"

template <typename T>
string_map<T>::string_map(): raiz(nullptr), _size(0),_claves(){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    Nodo* raiz=new Nodo;
    for (string s : d.claves()) {
        pair<string,T> p= make_pair(s,d.at(s));
        this->insert(p);
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    set<string> set = _claves;
    for(string s:set){
        erase(s);
    }
    delete raiz;
    raiz = nullptr;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    /*if(_size==0){
        raiz=new Nodo;
        raiz->siguientes(int('z')-int('a'), nullptr);
        raiz->definicion='"';

    }*/
}

template<typename T>
set<string> string_map<T>::claves() const {
    return _claves;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p){
    string s=p.first;
    if(_size==0){
        raiz=new Nodo;
    }
    Nodo* actual=raiz;
    for (int i=0; i<s.size(); i++) {
        if(actual->siguientes[int(s[i])]== nullptr){
            actual->siguientes[int(s[i])]=new Nodo;
        }
        actual=actual->siguientes[int(s[i])];
    }
    actual->definicion= new T(p.second);
    _size++;
    _claves.insert(p.first);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz== nullptr){
        return 0;
    } else {
        Nodo* actual=raiz;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->siguientes[int(clave[i])]== nullptr){
                return 0;
            }
            actual=actual->siguientes[int(clave[i])];
        }
        if (actual->definicion!= nullptr){
            return 1;
        }
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual=actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}


template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual=actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

template <typename T>
bool string_map<T>::masDeUnHijo(string_map<T>::Nodo *a) const{
    int c=0;
    for (int i = 0; i < 256; i++) {
        if(a->siguientes[i]!= nullptr){
            c++;
        }
    }
    return c>1;
}


template<typename T>
void string_map<T>::borrarDesde(int j, string clave) {
    //busco el ultimo

    if(j==0){
        delete raiz;
        raiz= nullptr;

    } else {
    Nodo* actual=raiz;
    Nodo* anterior;
    for(int i=0;i<=j;i++){
        anterior=actual;
        actual=actual->siguientes[int(clave[i])]; //actual sale siendo el primero que tengo que eliminar
    }

    anterior->siguientes[int(clave[j])] = nullptr; //pongo en nulo el lugar que quiero eliminar

    //ahora borro todos los nodos que me quedaron flotando:
    Nodo* aux;
    for(int i=j+1; i<clave.size();i++){
        aux = actual->siguientes[clave[i]];
        delete actual;
        actual = aux;
        }
    }
}


template <typename T>
void string_map<T>::erase(const string& clave) {
    if(count(clave)==1) {
        Nodo *actual = raiz;
        int j = 0;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->definicion != nullptr || masDeUnHijo(actual)) {
                j = i; //me guardo desde donde borro
            }
            actual = actual->siguientes[int(clave[i])];
        }
        // actual=actual->siguientes[int(clave[clave.size()-1])];
        if(noTieneHijos(actual)) {
            delete actual->definicion;
            actual->definicion = nullptr;
            borrarDesde(j, clave);
        } else {
            delete actual->definicion;
            actual->definicion = nullptr;
        }
        _claves.erase(clave);
    }
}

template<typename T>
bool string_map<T>::noTieneHijos(string_map::Nodo *a) const {
    for (int i = 0; i < 256; i++) {
        if(a->siguientes[i]!= nullptr){
            return false;
        }
    }
    return true;
}


template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    if(raiz== nullptr){
        return true;
    }
    return false;
}




