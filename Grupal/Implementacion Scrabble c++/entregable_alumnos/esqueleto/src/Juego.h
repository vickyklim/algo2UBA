#ifndef TP_JUEGODEPALABRAS_JUEGO_H
#define TP_JUEGODEPALABRAS_JUEGO_H

#include "Variante.h"
#include "Tablero.h"
#include <queue>


class Juego{
public:
    Juego(Nat cantJug, const Variante v, const queue<Letra> r);

    Variante verVariante() const;

    Tablero tablero();

    Nat tamanoTablero() const;

    Nat turno() const;

    bool jugadaValida(Ocurrencia o); //no toma como parametro el jugador porque va a ser el mismo que el _turno

    void ubicarFichas(Ocurrencia o); //no toma como parametro el jugador porque va a ser el mismo que el _turno

    Nat obtenerPuntaje(Nat jug);

    Nat cantidadFichasLetra(Nat cid, Letra l);

    Nat calcularPuntaje(Ocurrencia o);



private:
    Variante _variante;
    Nat _cantJug;
    queue<Letra> _repositorio;
    Tablero _tablero;
    vector<Nat> _puntaje;
    vector<vector<Nat>> _cantLetraJugador;
    Nat _turno;

    Nat sumarPuntajesVerticales(Celda c);

    Nat sumarPuntajesHorizontales(Celda c);

    bool esValidaHorizontal(Celda c) const;

    bool esValidaVertical(Celda c) const;
};

#endif //TP_JUEGODEPALABRAS_JUEGO_H