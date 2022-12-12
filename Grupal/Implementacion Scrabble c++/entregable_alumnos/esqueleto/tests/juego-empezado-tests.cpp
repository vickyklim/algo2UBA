#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Servidor.h"

#include "utils/PalabrasComunes.h"
#include "utils/NotificacionesUtils.h"
#include "utils/Repositorio.h"
#include "utils/Puntajes.h"

class JuegoEmpezadoTest : public testing::Test {
protected:
    Nat cantJugadores = 3;
    Nat tamanoTab = 10;
    Nat cantFichas = 5;

    map<Letra, Nat> puntajes;
    set<vector<Letra> > palabrasLegitimas;
    Repositorio repo;

    Fachada_Variante variante;
    Fachada_Servidor fachada;

    JuegoEmpezadoTest():
      puntajes(puntajesIngles),
      palabrasLegitimas(begin(palabrasComunes), end(palabrasComunes)),
      repo(RepositorioGrande::repositorioChico()),
      variante(tamanoTab, cantFichas, puntajes, palabrasLegitimas),
      fachada(cantJugadores, variante, repo)
      {
        for (Nat i = 0; i < cantJugadores; i++){
            fachada.conectarCliente();
        }
      }

};

TEST_F(JuegoEmpezadoTest, jugador_reciba_mal_si_juega_en_otro_turno) {
    // limpiar notifs
    fachada.notificaciones(2);

    fachada.recibirMensaje(2, {{1, 2, 'f'}, {1, 3, 'a'}});

    compareNotificaciones(fachada.notificaciones(2), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoEmpezadoTest, jugador_recibe_mal_si_juega_fichas_que_no_tiene) {
    // limpiar notifs
    fachada.notificaciones(0);

    fachada.recibirMensaje(0, {{1, 2, 'a'}});

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoEmpezadoTest, jugador_recibe_mal_si_posiciones_ocupadas) {
    fachada.recibirMensaje(0, {{1, 2, 'a'}});

    // Limpiar notifs
    fachada.notificaciones(1);
    fachada.recibirMensaje(1, {{1, 2, 'd'}, {2, 2, 'e'}});

    compareNotificaciones(fachada.notificaciones(1), {
        Notificacion::nuevaMal()
    });
};

TEST_F(JuegoEmpezadoTest, jugadores_reciben_notificaciones_ante_jugada_valida) {
    fachada.notificaciones(0);
    fachada.notificaciones(1);
    fachada.notificaciones(2);

    Ocurrencia o = {{1, 1, 'e'}};
    fachada.recibirMensaje(0, o);

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaUbicar(0, o),
            Notificacion::nuevaSumaPuntos(0, 2),
            Notificacion::nuevaReponer({'a'}),
            Notificacion::nuevaTurnoDe(1)
    });

    for (Nat j = 1; j < cantJugadores; j++) {
        compareNotificaciones(fachada.notificaciones(j), {
                Notificacion::nuevaUbicar(0, o),
                Notificacion::nuevaSumaPuntos(0, 2),
                Notificacion::nuevaTurnoDe(1)
        });
    }

};

TEST_F(JuegoEmpezadoTest, jugadores_reciben_notificaciones_ante_jugada_vacia) {
    fachada.notificaciones(0);
    fachada.notificaciones(1);
    fachada.notificaciones(2);

    Ocurrencia o = {};
    fachada.recibirMensaje(0, o);

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaUbicar(0, o),
            Notificacion::nuevaSumaPuntos(0, 0),
            Notificacion::nuevaReponer({}),
            Notificacion::nuevaTurnoDe(1)
    });

    for (Nat j = 1; j < cantJugadores; j++) {
        compareNotificaciones(fachada.notificaciones(j), {
                Notificacion::nuevaUbicar(0, o),
                Notificacion::nuevaSumaPuntos(0, 0),
                Notificacion::nuevaTurnoDe(1)
        });
    }

};


TEST_F(JuegoEmpezadoTest, jugador_recibe_mal_si_posiciones_diagonales) {
    // Limpiar notifs
    fachada.notificaciones(0);
    fachada.recibirMensaje(0, {{1, 1, 'd'}, {2, 2, 'o'}});

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaMal()
    });
};


