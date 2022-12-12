#include "Tablero.h"
#include <utility>

using namespace std;

Tablero::Tablero(Nat n){
    _tamano=n;
    vector<vector<pair<bool, Letra>>> tab={};
    for (int i = 0; i < n; i++) {
        vector<pair<bool,Letra>> fila={};
        for (int j = 0; j < n; j++) {
            fila.push_back(make_pair(false, 'a'));
        }
        tab.push_back(fila);
    }
    _tab=tab;
}

void Tablero::ponerLetra(int i, int j, Letra l) {
    _tab[i][j]= make_pair(true, l);
}

void Tablero::ubicarFichasTablero(Ocurrencia o) {
    for (typename Ocurrencia::iterator it = o.begin(); it != o.end(); it++) {
        _tab[get<0>(*it)][get<1>(*it)]= make_pair(true, get<2>(*it));
    }
}

void Tablero::sacarLetra(int i, int j, Letra l) {
    _tab[i][j]= make_pair(false, 'a');
}

pair<bool, Letra> Tablero::obtenerContenido(int i, int j) const{
    return _tab[i][j];
}

bool Tablero::celdaLibre(Celda c) const{
    return not get<0>(_tab[get<0>(c)][get<1>(c)]);
}


Nat Tablero::tamanoTablero() const{
    return _tamano;
}

bool Tablero::hayAgujerosHorizontales(Ocurrencia o) const{
    Celda c=*o.begin();
    Celda inicio=*o.begin();
    Celda fin=*o.begin();
    int i=get<1>(inicio);
    int j=get<1>(fin);

    while(i>=0 && not this->celdaLibre(make_tuple(get<0>(c),i,get<1>(obtenerContenido(get<0>(c),i))))){
        inicio = make_tuple(get<0>(c),i,get<1>(obtenerContenido(get<0>(c),i)));
        i--;
    }

    while(j<this->tamanoTablero() && not celdaLibre(make_tuple(get<0>(c),j,get<1>(obtenerContenido(get<0>(c),j))))){
        fin= make_tuple(get<0>(c),j,get<1>(obtenerContenido(get<0>(c),j)));
        j++;
    }

    Nat min= get<1>(inicio);
    Nat max= get<1>(fin);

    for(Celda c:o){
        if(get<1>(c)<min){
            min= get<1>(c);
        }
        if(get<1>(c)>max){
            max= get<1>(c);
        }
    }

    for(i=min; i<=max; i++){
        if(celdaLibre(make_tuple(get<0>(*o.begin()),i,'a'))){
            return true;
        }
    }
    return false;
}

bool Tablero::hayAgujerosVerticales(Ocurrencia o) const {
    Celda c=*o.begin();
    Celda inicio=*o.begin();
    Celda fin=*o.begin();
    int i=get<0>(inicio);
    int j=get<0>(fin);

    while (i >= 0 && not celdaLibre(make_tuple(i, get<1>(c), get<1>(obtenerContenido(i, get<1>(c)))))) {
        inicio = make_tuple(i, get<1>(c), get<1>(obtenerContenido(i, get<1>(c))));
        i--;
    }


    while (j < this->tamanoTablero() && not celdaLibre(make_tuple(j, get<1>(c), get<1>(obtenerContenido(j, get<1>(c)))))) {
        fin = make_tuple(j, get<1>(c), get<1>(obtenerContenido(j, get<1>(c))));
        j++;
    }

    Nat min= get<0>(inicio);
    Nat max= get<0>(fin);

    for(Celda c:o){
        if(get<0>(c)<min){
            min= get<0>(c);
        }
        if(get<0>(c)>max){
            max= get<0>(c);
        }
    }

    for(i=min; i<=max; i++){
        if(celdaLibre(make_tuple(i, get<1>(*o.begin()),'a'))){
            return true;
        }
    }
    return false;
}


