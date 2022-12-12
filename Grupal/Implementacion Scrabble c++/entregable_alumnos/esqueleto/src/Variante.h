#ifndef TP_JUEGODEPALABRAS_VARIANTE_H
#define TP_JUEGODEPALABRAS_VARIANTE_H


#include "ConjTrie.h"

class Variante {
public:
    /**
     * Construye una Fachada_Variante a partir de los parametros de las variantes
     */
    Variante(
            Nat tamanioTab,
            Nat fichas,
            const vector<Nat>& puntajeLetra,
            // const ConjTrie* palabrasLegitimas ANTERIOR
            const set<vector<Letra>> palabrasLegitimas
    );



    /**
     * Retorna el tamano del tablero de la variante
     */
    Nat tamanioTabVariante() const;

    /**
     * Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat cantFichas() const;

    /**
     * Retorna el puntaje de la letra l
     */
    Nat puntajeLetra(Letra l) const;

    /**
     * Indica si una palabra es legitima o no
     */
    bool esPalabraLegitima(const Palabra& pal) const;

    // const ConjTrie* palabrasLegitimas() const;

    const Nat altura(){
        return _lmax;
    };



private:
    Nat _tamanioTab;
    Nat _cantFichas;
    vector<Nat> _puntajeLetra;
    const ConjTrie _palabrasLegitimas;
    const Nat _lmax;

};
#endif // VARIANTE_H