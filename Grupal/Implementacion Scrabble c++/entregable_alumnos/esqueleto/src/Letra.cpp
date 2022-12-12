#include "Letra.h"

Nat ord (Letra l) {
    return Nat(l) -'a';
}

Letra inversaDeOrd(Nat n) {
    assert(0 <= n && n < TAMANIO_ALFABETO);

    return char('a' + n);
}
