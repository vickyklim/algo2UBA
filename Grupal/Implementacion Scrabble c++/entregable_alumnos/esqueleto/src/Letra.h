#ifndef LETRA_H
#define LETRA_H

#include "Tipos.h"

constexpr int TAMANIO_ALFABETO = int('z' - 'a') + 1;
Nat ord (Letra l);
Letra inversaDeOrd(Nat n);

#endif // LETRA_H