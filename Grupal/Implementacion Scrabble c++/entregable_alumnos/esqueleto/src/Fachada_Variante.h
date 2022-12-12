#ifndef FACHADA_VARIANTE_H
#define FACHADA_VARIANTE_H


#include "Variante.h"
#include "auxiliares.h"


class Fachada_Variante {
public:
    /**
     * Construye una Fachada_Variante a partir de los parametros de las variantes
     */
    Fachada_Variante(
            Nat tamanoTab,
            Nat cantFichas,
            const map<Letra, Nat> &puntajes,
            const set<vector<Letra>> palabrasLegitimas
    ): _variante(tamanoTab,cantFichas,convertirVector(puntajes),palabrasLegitimas){
    };


    /**
     * Retorna el tamano del tablero de la variante
     */
    Nat tamanoTablero() const{
        return _variante.tamanioTabVariante();
    }

    /**
     * Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat fichas() const{
        return _variante.cantFichas();
    }

    /**
     * Retorna el puntaje de la letra l
     */
    Nat puntajeLetra(Letra l) const{
        return _variante.puntajeLetra(l);
    }

    /**
     * Indica si una palabra es legitima o no
     */
    bool palabraLegitima(const Palabra& palabra) const{
        return _variante.esPalabraLegitima(palabra);
    }

    Variante devolverVariante() const{
        return _variante;
    }

private:
    Variante _variante;
};

#endif //FACHADA_VARIANTE_H
