
#include "gtest-1.8.1/gtest.h"

#include "../src/Tipos.h"
#include "../src/Letra.h"


TEST(testsDeLetra, primerLetraEsA) {

    Letra l = inversaDeOrd(0);

    EXPECT_EQ('a', l);

    Nat n = ord('a');

    EXPECT_EQ(0, n);

    
}

TEST(testsDeLetra, ultimaLetraEsZ) {

    Letra l = inversaDeOrd(TAMANIO_ALFABETO-1);

    EXPECT_EQ('z', l);

    Nat n = ord('z');

    EXPECT_EQ(TAMANIO_ALFABETO-1, n);

    
}