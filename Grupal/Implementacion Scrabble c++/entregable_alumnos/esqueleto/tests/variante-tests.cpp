#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Variante.h"

#include "utils/PalabrasComunes.h"

class VarianteTest : public testing::Test {
protected:
    Nat tamanoTab = 10;
    Nat cantFichas = 2;

    map<Letra, Nat> puntajes;
    set<vector<Letra> > palabrasLegitimas;

    Fachada_Variante variante;

    VarianteTest():
      puntajes({ {'a',  1 }, {'x' , 20}, {'z', 20}}),
      palabrasLegitimas(begin(palabrasComunes), end(palabrasComunes)),
      variante(tamanoTab, cantFichas, puntajes, palabrasLegitimas)
      {}

};

TEST_F(VarianteTest, variante_tiene_datos_correctos) {
    EXPECT_EQ(variante.tamanoTablero(), tamanoTab);
    EXPECT_EQ(variante.fichas(), cantFichas);

    EXPECT_EQ(variante.puntajeLetra('x'), 20);
    EXPECT_EQ(variante.puntajeLetra('z'), 20);
    EXPECT_EQ(variante.puntajeLetra('l'), 1);

    EXPECT_TRUE(variante.palabraLegitima({'d', 'e'}));
    EXPECT_TRUE(variante.palabraLegitima({'t', 'o', 'd', 'o', 's'}));
    EXPECT_FALSE(variante.palabraLegitima({'d', 'd'}));
};

TEST_F(VarianteTest, variante_no_tiene_aliasing) {
    tamanoTab = 22;
    cantFichas = 1;
    EXPECT_EQ(variante.tamanoTablero(), 10);
    EXPECT_EQ(variante.fichas(), 2);

    puntajes = {};
    EXPECT_EQ(variante.puntajeLetra('x'), 20);
    EXPECT_EQ(variante.puntajeLetra('z'), 20);
    EXPECT_EQ(variante.puntajeLetra('l'), 1);

    palabrasLegitimas = {{'d', 'd'}};
    EXPECT_TRUE(variante.palabraLegitima({'d', 'e'}));
    EXPECT_TRUE(variante.palabraLegitima({'t', 'o', 'd', 'o', 's'}));
    EXPECT_FALSE(variante.palabraLegitima({'d', 'd'}));
};
