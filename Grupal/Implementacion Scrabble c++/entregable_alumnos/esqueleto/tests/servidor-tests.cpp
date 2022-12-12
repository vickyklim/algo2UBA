#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Servidor.h"

#include "utils/NotificacionesUtils.h"
#include "utils/PalabrasComunes.h"

class ServidorTest : public testing::Test {
protected:
    map<Letra, Nat> puntajes;
    set<vector<Letra> > palabrasLegitimas;
    Repositorio repo;

    void SetUp() {
        puntajes = { { 
            'a',  1 }, {'x' , 20}, {'z', 20} 
            };

        palabrasLegitimas = set<vector<Letra> >(begin(palabrasComunes), end(palabrasComunes));

        repo = {'a', 'a', 'f', 'e', 't', 'g', 'w', 'r', 'e', 'a', 'a', 'f', 'e', 't', 'g', 'w', 'r', 'e', 'a', 'a', 'f', 'e', 't', 'g', 'w', 'r', 'e', 'a', 'a', 'f', 'e', 't', 'g', 'w', 'r', 'e'};

    }
};

TEST_F(ServidorTest, crear_servidor_tiene_cero_jugadores_conectados) {
    Nat cantJugadores = 3; 
    Nat tamanoTab = 10;
    Nat cantFichas = 7;

    Fachada_Variante var(tamanoTab, cantFichas, puntajes, palabrasLegitimas);
    Fachada_Servidor f(cantJugadores, var, repo);

    EXPECT_EQ(f.jugadoresConectados(), 0);
    EXPECT_EQ(f.jugadoresEsperados(), cantJugadores);
};

TEST_F(ServidorTest, despues_de_conectar_jugador_hay_un_conectado) {
    Nat cantJugadores = 3; 
    Nat tamanoTab = 10;
    Nat cantFichas = 7;

    Fachada_Variante var(tamanoTab, cantFichas, puntajes, palabrasLegitimas);
    Fachada_Servidor f(cantJugadores, var, repo);

    f.conectarCliente();
    EXPECT_EQ(f.jugadoresConectados(), 1);
    EXPECT_EQ(f.jugadoresEsperados(), cantJugadores);
};

TEST_F(ServidorTest, despues_de_conectar_cuatro_jugadores_cada_uno_recibe_su_id) {
    Nat cantJugadores = 4; 
    Nat tamanoTab = 10;
    Nat cantFichas = 7;

    Fachada_Variante var(tamanoTab, cantFichas, puntajes, palabrasLegitimas);
    Fachada_Servidor f(cantJugadores, var, repo);

    IdCliente id1 = f.conectarCliente();
    EXPECT_EQ(f.jugadoresConectados(), 1);
    EXPECT_EQ(f.jugadoresEsperados(), cantJugadores);

    compareNotificaciones(f.notificaciones(id1), {
        Notificacion::nuevaIdCliente(id1)
    });

    IdCliente id2 = f.conectarCliente();
    EXPECT_EQ(2, f.jugadoresConectados());
    EXPECT_EQ(f.jugadoresEsperados(), cantJugadores);

    EXPECT_EQ(0, f.notificaciones(id1).size());

    IdCliente id3 = f.conectarCliente();
    EXPECT_EQ(3, f.jugadoresConectados());

    compareNotificaciones(f.notificaciones(id2), {
            Notificacion::nuevaIdCliente(id2)
    });

    compareNotificaciones(f.notificaciones(id3), {
            Notificacion::nuevaIdCliente(id3)
    });
};

TEST_F(ServidorTest, cuando_estan_todos_los_jugadores_se_envian_notificaciones_de_empezar) {
    Nat cantJugadores = 2; 
    Nat tamanoTab = 10;
    Nat cantFichas = 3;

    Fachada_Variante var(tamanoTab, cantFichas, puntajes, palabrasLegitimas);
    Fachada_Servidor f(cantJugadores, var, repo);

    IdCliente id1 = f.conectarCliente();
    IdCliente id2 = f.conectarCliente();

    EXPECT_EQ(f.jugadoresConectados(), cantJugadores);

    compareNotificaciones(f.notificaciones(id1), {
            Notificacion::nuevaIdCliente(id1),
            Notificacion::nuevaEmpezar(tamanoTab),
            Notificacion::nuevaTurnoDe(id1),
            Notificacion::nuevaReponer({ 'a', 'a', 'f'})
    });

    compareNotificaciones(f.notificaciones(id2), {
            Notificacion::nuevaIdCliente(id2),
            Notificacion::nuevaEmpezar(tamanoTab),
            Notificacion::nuevaTurnoDe(id1),
            Notificacion::nuevaReponer({ 'e', 't', 'g'})
    });
};


TEST_F(ServidorTest, jugador_1_ubica_antes_de_empezar_esta_mal) {
    Nat cantJugadores = 3;
    Nat tamanoTab = 10;
    Nat cantFichas = 7;

    Fachada_Variante var(tamanoTab, cantFichas, puntajes, palabrasLegitimas);
    Fachada_Servidor f(cantJugadores, var, repo);

    IdCliente id1 = f.conectarCliente();
    IdCliente id2 = f.conectarCliente();

    f.recibirMensaje(id1, {{0,0, 'a'}});

    compareNotificaciones(f.notificaciones(id1), {
            Notificacion::nuevaIdCliente(id1),
            Notificacion::nuevaMal()
    });

    compareNotificaciones(f.notificaciones(id2), {
            Notificacion::nuevaIdCliente(id2)
    });
}