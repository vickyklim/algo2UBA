#ifndef FACHADA_JUEGO_H
#define FACHADA_JUEGO_H


#include "Fachada_Variante.h"
#include "Juego.h"
#include "Tablero.h"
#include <queue>
#include "auxiliares.h"

class Fachada_Juego {
public:
    /**
     * Construye un juego a partir de la cantidad de jugadores k, la variante v y el repositorio r
     *
     * Complejidad: O(tamanoTab**2 + ALPHABET_SIZE*cantJugadores + cantFichas*cantJugadores)
     */
    Fachada_Juego(Nat k, const Fachada_Variante& v, const Repositorio& r):
    _juego(k,v.devolverVariante(), pasarAQueue(r)), _fachVariante(v) {
    }

    /**
     * Ubica una Ocurrencia o en el juego
     *
     * Complejidad: O(m)
     *   donde m es el numero de fichas que se ubican
     */
    void ubicar(const Ocurrencia& o){
        return _juego.ubicarFichas(o);
    }


    /**
     * Retorna el id del cliente al cual le toca jugar
     *
     * Complejidad: O(1)
     */
    IdCliente turno(){
        return _juego.turno();
    }

    /**
     * Retorna informacion sobre la variante del juego
     *
     * Complejidad: O(1)
     */
    const Fachada_Variante& variante(){
        return _fachVariante;
    }

    /**
     * Determina si una jugada es valida o no
     *
     * Complejidad: O(Lmax ** 2)
     */
    bool jugadaValida(const Ocurrencia& o){
        return _juego.jugadaValida(o);
    }

    /**
     * Retorna true sii la coordenada se encuentra ocupada.
     *
     * Complejidad: O(1)
     */
    bool hayLetra(Nat x, Nat y){
        return get<0>(_juego.tablero().obtenerContenido(x,y));
    }

    /**
     * Obtiene el contenido del tablero en una coordenada.
     *
     * Complejidad: O(1)
     */
    Letra letra(Nat i, Nat j){
        return get<1>(_juego.tablero().obtenerContenido(i,j));
    }

    /**
     * Retorna el puntaje del jugador id
     *
     * Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.
     */
    Nat puntaje(IdCliente id){
        return _juego.obtenerPuntaje(id);
    }


    /**
     * Dado un jugador id y una letra l, retorna cuantas fichas tiene el jugador de dicha letra.
     *
     * Complejidad: O(1)
     */
    Nat cantFicha(IdCliente id, Letra l){
        return _juego.cantidadFichasLetra(id,l);
    }

private:
    Juego _juego;

    Fachada_Variante _fachVariante;
};

#endif // FACHADA_JUEGO_H
