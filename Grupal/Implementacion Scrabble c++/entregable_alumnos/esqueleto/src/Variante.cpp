#include "Variante.h"
#include "auxiliares.h"

Variante::Variante(Nat tamanioTab, Nat fichas, const vector<Nat> &puntajeLetra, const set<vector<Letra>> palabrasLegitimas):
_palabrasLegitimas(pasarATrie(palabrasLegitimas)), _lmax(_palabrasLegitimas.altura()){
    _tamanioTab = tamanioTab;
    _cantFichas = fichas;
    _puntajeLetra = puntajeLetra;
}

Nat Variante::tamanioTabVariante() const {
    return _tamanioTab;
}

Nat Variante::cantFichas() const {
    return _cantFichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return _puntajeLetra[ord(l)];
}

bool Variante::esPalabraLegitima(const Palabra &pal) const{
    return _palabrasLegitimas.pertenece(pal);
}

/* const ConjTrie* Variante::palabrasLegitimas() const {
    return _palabrasLegitimas;
} */



