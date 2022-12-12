#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Juego.h"

#include "utils/PalabrasComunes.h"

class JuegosTests : public testing::Test{
protected:
    Nat cantJugadores = 3;
    Nat tamanoTab = 10;
    Nat cantFichas = 2;

    map<Letra, Nat> puntajes;
    set<vector<Letra>> palabrasLegitimas;
    Repositorio repo;

    void SetUp()
    {
        puntajes = {{'a', 1}, {'q' , 0} ,{'x', 20}, {'z', 20}};

        palabrasLegitimas = set<vector<Letra>>(begin(palabrasComunes), end(palabrasComunes));
        repo = {'a', 'a', 'f', 'e', 't', 'g', 'w', 'r', 'e'};
    }
};

TEST_F(JuegosTests, juego_recien_empieza){
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_EQ(0, juego.turno());
    EXPECT_EQ(0, juego.puntaje(0));
    EXPECT_EQ(0, juego.puntaje(1));
};

TEST_F(JuegosTests, crear_juego_tiene_tablero_vacio) {
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_EQ(juego.variante().tamanoTablero(), tamanoTab);

    for (Nat i = 0; i < tamanoTab; i++){
        for (Nat j = 0; j < tamanoTab; j++){
            EXPECT_FALSE(juego.hayLetra(i, j));
        }
    }
};

TEST_F(JuegosTests, ubicar_vacio_no_da_puntos){
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    juego.ubicar({});

    EXPECT_EQ(1, juego.turno());
    EXPECT_EQ(0, juego.puntaje(0));
    EXPECT_EQ(0, juego.puntaje(1));
};


TEST_F(JuegosTests, ubicar_a_da_dos_puntos){
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    juego.ubicar({ {0, 0, 'a'}});

    EXPECT_TRUE(juego.hayLetra(0,0));
    EXPECT_EQ(juego.letra(0, 0), 'a');
    EXPECT_EQ(1, juego.turno());
    EXPECT_EQ(2, juego.puntaje(0));
    EXPECT_EQ(0, juego.puntaje(1));
};

TEST_F(JuegosTests, jugada_discontigua_ilegitima){
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_FALSE(juego.jugadaValida({{0, 0, 'a'}, {0, 2, 'a'}}));
};

TEST_F(JuegosTests, jugada_letra_sola_valida){
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_TRUE(juego.jugadaValida({{0, 0, 'a'}}));
};

TEST_F(JuegosTests, fichas_se_reparten_correctamente) {
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_EQ(juego.cantFicha(0, 'a'), 2);
    EXPECT_EQ(juego.cantFicha(1, 'f'), 1);
    EXPECT_EQ(juego.cantFicha(1, 'e'), 1);

    juego.ubicar({{0, 0, 'a'}});

    EXPECT_EQ(juego.cantFicha(0, 'a'), 1);
    EXPECT_EQ(juego.cantFicha(0, 't'), 1);
    EXPECT_EQ(juego.cantFicha(1, 'f'), 1);
    EXPECT_EQ(juego.cantFicha(1, 'e'), 1);

}