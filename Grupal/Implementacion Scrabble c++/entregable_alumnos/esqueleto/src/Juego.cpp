#include "Juego.h"


Juego::Juego(Nat cantJug, Variante v, queue<Letra> r): _tablero(v.tamanioTabVariante()), _variante(v),
_puntaje(cantJug,0),_repositorio(r), _cantJug(cantJug){
    vector<vector<Nat>> cantLetra={};
    for (int i=0; i<cantJug; i++){
        vector<Nat> fichas (TAMANIO_ALFABETO);
        for(int j=0; j<v.cantFichas(); j++){
            fichas[ord(_repositorio.front())]=fichas[ord(_repositorio.front())]+1;
            _repositorio.pop();
        }
        cantLetra.push_back(fichas);
    }
    _cantLetraJugador=cantLetra;
    _turno=0;
}

Variante Juego::verVariante() const {
    return _variante;
}

Tablero Juego::tablero() {
    return _tablero;
}

Nat Juego::tamanoTablero() const{
    return _tablero.tamanoTablero();
}

Nat Juego::turno() const {
    return _turno;
}

bool esVertical(Ocurrencia o){ //Decidimos ponerla en juego.cpp porque no cambiaba mucho con respecto a nuestro diseño
    Nat n=get<1>(*o.begin());

    for(Celda c:o){
        if(get<1>(c)!=n){
            return false;
        }
    }
    return true;
}

bool esHorizontal(Ocurrencia o){  //Decidimos ponerla en juego.cpp porque no cambiaba mucho con respecto a nuestro diseño
    Nat n=get<0>(*o.begin());
    for(Celda c:o){
        if(get<0>(c)!=n){
            return false;
        }
    }
    return true;
}

bool Juego::jugadaValida(Ocurrencia o) {
    /*Chequeo si la longitud de la ocurrencia es menor a la palabra legitima mas larga*/

    if(o.size()==0){
        return true;
    }

    if(o.size()> _variante.altura()){
        return false;
    }

    //Verifico que las fichas esten en mano, que las celdas estén libres y que el rango pertenezca al tablero
    //La complejidad es de O(m) con m acotado por lmax, por lo que es O(Lmax)

    for (Celda c: o) {
        if(_cantLetraJugador[_turno][ord(get<2>(c))]==0
        || not _tablero.celdaLibre(c)
        || get<0>(c) >= _tablero.tamanoTablero() || get<0>(c) < 0
        || get<1>(c) >= _tablero.tamanoTablero() || get<1>(c)<0){
            return false;
        }
    }

    //Chequeo que sea horizontal o vertical. O(Lmax+Lmax)
    bool palHor= esHorizontal(o);
    bool palVer= esVertical(o);
    if(not(palVer || palHor)){
        return false;
    }

    //Pongo las fichas en el tablero O(Lmax)
    for(Celda c:o){
        _tablero.ponerLetra(get<0>(c), get<1>(c), get<2>(c));
    }

    //Chequeo palabras validas si es horizontal. O(Lmax^2)
    if(palHor){
        if(this->esValidaHorizontal(*o.begin()) && not _tablero.hayAgujerosHorizontales(o)){
            for(Celda c:o){
                if(not this->esValidaVertical(c)){
                    return false;
                }
            }
        } else {
            return false;
        }
    }

    //Chequeo palabras validas si es vertical. O(Lmax^2)
    if(palVer){
        if(this->esValidaVertical(*o.begin()) && not _tablero.hayAgujerosVerticales(o)){
            for(Celda c:o){
                if(not this->esValidaHorizontal(c)){
                    return false;
                }
            }
        } else {
            return false;
        }
    }



    //Saco las fichas. O(Lmax)
    for(Celda c:o){
        _tablero.sacarLetra(get<0>(c),get<1>(c),get<2>(c));
    }

    return true;
}

bool Juego::esValidaHorizontal(Celda c) const {
    Tablero t=_tablero;
    Celda pivote=c;
    Celda inicio=pivote;
    Celda fin=pivote;
    int i=get<1>(inicio);
    int j=get<1>(fin);

    while(i>=0 && not _tablero.celdaLibre(make_tuple(get<0>(c),i,get<1>(_tablero.obtenerContenido(get<0>(c),i))))){
        inicio = make_tuple(get<0>(c),i,get<1>(_tablero.obtenerContenido(get<0>(c),i)));
        i--;
    }

    while(j<this->tamanoTablero() && not _tablero.celdaLibre(make_tuple(get<0>(c),j,get<1>(_tablero.obtenerContenido(get<0>(c),j))))){
        fin= make_tuple(get<0>(c),j,get<1>(_tablero.obtenerContenido(get<0>(c),j)));
        j++;
    }

    Palabra pal={};

    for(int k=get<1>(inicio); k<= get<1>(fin); k++){
        pal.push_back(get<1>(_tablero.obtenerContenido(get<0>(c), k)));
    }


    if(pal.size()-1 != get<1>(fin)- get<1>(inicio)){
        return false;
    }

    if(_variante.esPalabraLegitima(pal)){
        return true;
    } else{
        return false;
    }
}

bool Juego::esValidaVertical(Celda c) const {
    Tablero t = _tablero;
    Celda pivote = c;
    Celda inicio = pivote;
    Celda fin = pivote;
    int i = get<0>(inicio);
    int j = get<0>(fin);


    while (i >= 0 && not _tablero.celdaLibre(make_tuple(i, get<1>(c), get<1>(_tablero.obtenerContenido(i, get<1>(c)))))) {
        inicio = make_tuple(i, get<1>(c), get<1>(_tablero.obtenerContenido(i, get<1>(c))));
        i--;
    }


    while (j < this->tamanoTablero() && not _tablero.celdaLibre(make_tuple(j, get<1>(c), get<1>(_tablero.obtenerContenido(j, get<1>(c)))))) {
            fin = make_tuple(j, get<1>(c), get<1>(_tablero.obtenerContenido(j, get<1>(c))));
            j++;
    }


        Palabra pal = {};

        for (int k = get<0>(inicio); k <= get<0>(fin); k++) {
            pal.push_back(get<1>(_tablero.obtenerContenido(k, get<1>(c))));
        }

    if(pal.size()-1 != get<0>(fin)- get<0>(inicio)){
        return false;
    }

        if (_variante.esPalabraLegitima(pal)) {
            return true;
        } else {
            return false;
        }
    }

    void Juego::ubicarFichas(Ocurrencia o) {
        if(o.size()!=0){
            _tablero.ubicarFichasTablero(o);
            for (Celda c: o) {
                _cantLetraJugador[_turno][ord(get<2>(c))] = _cantLetraJugador[_turno][ord(get<2>(c))] - 1;
                _cantLetraJugador[_turno][ord(_repositorio.front())] = _cantLetraJugador[_turno][ord(_repositorio.front())] + 1;
                _repositorio.pop();
            }
            _puntaje[_turno]=_puntaje[_turno]+ calcularPuntaje(o);
        }
        _turno = (_turno + 1) % _cantJug;
    }


    Nat Juego::obtenerPuntaje(Nat jug) {
        return _puntaje[jug];
    }


    Nat Juego::cantidadFichasLetra(Nat cid, Letra l) {
        return _cantLetraJugador[cid][ord(l)];
    }

    Nat Juego::calcularPuntaje(Ocurrencia o) {
        Nat puntaje = 0;
            if (esHorizontal(o)) {
                puntaje=puntaje+sumarPuntajesHorizontales(*o.begin());
                for (Celda c: o) {
                    puntaje = puntaje + sumarPuntajesVerticales(c);
                }
            } else {
                puntaje=puntaje+sumarPuntajesVerticales(*o.begin());
                for (Celda c: o) {
                    puntaje = puntaje + sumarPuntajesHorizontales(c);
                }
            }
        return puntaje;
    }


Nat Juego::sumarPuntajesVerticales(Celda posicion) {
    Nat lmax = _variante.altura();
    Celda pivote = posicion;
    Celda inicio = pivote;
    Celda fin = pivote;
    int i = get<0>(inicio);
    int j = get<0>(fin);


    while (i >= 0 && not _tablero.celdaLibre(make_tuple(i, get<1>(posicion), get<1>(_tablero.obtenerContenido(i, get<1>(posicion)))))) {
        inicio = make_tuple(i, get<1>(posicion), get<1>(_tablero.obtenerContenido(i, get<1>(posicion))));
        i--;
    }


    while (j < this->tamanoTablero() && not _tablero.celdaLibre(make_tuple(j, get<1>(posicion), get<1>(_tablero.obtenerContenido(j, get<1>(posicion)))))) {
        fin = make_tuple(j, get<1>(posicion), get<1>(_tablero.obtenerContenido(j, get<1>(posicion))));
        j++;
    }


    Palabra pal = {};

    for (int k = get<0>(inicio); k <= get<0>(fin); k++) {
        pal.push_back(get<1>(_tablero.obtenerContenido(k, get<1>(posicion))));
    }


    Nat puntajePalabra = 0;
        for (Letra l: pal) {
            puntajePalabra = puntajePalabra + _variante.puntajeLetra(l);
        }
        return puntajePalabra;
}

Nat Juego::sumarPuntajesHorizontales(Celda posicion) {
    Nat lmax = _variante.altura();
    Celda pivote = posicion;
    Celda inicio = pivote;
    Celda fin = pivote;
    int i = get<1>(inicio);
    int j = get<1>(fin);


    while (i >= 0 && not _tablero.celdaLibre(make_tuple(get<0>(posicion),i, get<1>(_tablero.obtenerContenido(get<0>(posicion), i))))) {
        inicio = make_tuple(get<0>(posicion),i, get<1>(_tablero.obtenerContenido(get<0>(posicion), i)));
        i--;
    }


    while (j < this->tamanoTablero() && not _tablero.celdaLibre(make_tuple(get<0>(posicion),j, get<1>(_tablero.obtenerContenido(get<0>(posicion),j))))) {
        fin = make_tuple(get<0>(posicion),j, get<1>(_tablero.obtenerContenido(get<0>(posicion),j)));
        j++;
    }


    Palabra pal = {};

    for (int k = get<1>(inicio); k <= get<1>(fin); k++) {
        pal.push_back(get<1>(_tablero.obtenerContenido(get<0>(posicion), k)));
    }


    Nat puntajePalabra = 0;
    for (Letra l: pal) {
        puntajePalabra = puntajePalabra + _variante.puntajeLetra(l);
    }
    return puntajePalabra;
}
