#ifndef TP_JUEGODEPALABRAS_TABLERO_H
#define TP_JUEGODEPALABRAS_TABLERO_H
#include "Letra.h"

class Tablero{
public:
    Tablero(Nat n);

    void ponerLetra(int i, int j, Letra l);

    void ubicarFichasTablero(Ocurrencia o);

    void sacarLetra(int i, int j, Letra l);

    pair<bool, Letra> obtenerContenido(int i, int j) const;

    bool celdaLibre(Celda c) const;


    Nat tamanoTablero() const;

    bool hayAgujerosVerticales(Ocurrencia o) const;

    bool hayAgujerosHorizontales(Ocurrencia o) const;



private:
    Nat _tamano;
    vector<vector<pair<bool, Letra>>> _tab;

};

#endif // TABLERO_H

