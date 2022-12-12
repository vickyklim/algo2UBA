#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Servidor.h"

#include "utils/Repositorio.h"
#include "utils/Puntajes.h"
#include "utils/NotificacionesUtils.h"
#include "utils/PalabrasComunes.h"

class JuegoGrandeTest : public testing::Test {
protected:
    Nat cantJugadores = 30;
    Nat tamanoTab = 100;
    Nat cantFichas = 100;

    map<Letra, Nat> puntajes;
    set<vector<Letra> > palabrasLegitimas;
    Repositorio repo;

    Fachada_Variante variante;
    Fachada_Servidor fachada;

    JuegoGrandeTest():
      puntajes(puntajesIngles),
      palabrasLegitimas(begin(palabrasComunes), end(palabrasComunes)),
      repo(RepositorioGrande::repositorioGrande()),
      variante(tamanoTab, cantFichas, puntajes, palabrasLegitimas),
      fachada(cantJugadores, variante, repo)
      {
        for (Nat i = 0; i < cantJugadores; i++){
            fachada.conectarCliente();
        }
      }

};


TEST_F(JuegoGrandeTest, jugadores_reciben_notificaciones_ante_jugada_valida) {
    for (Nat j = 0; j < cantJugadores; j++) {
        fachada.notificaciones(j);
    }

    Ocurrencia o = {{1, 5, 'r'}, {1, 1, 'm'}, {1, 2, 'a'}, {1, 4, 'o'}, {1, 3, 'y'}};
    fachada.recibirMensaje(0, o);

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaUbicar(0, o),
            Notificacion::nuevaSumaPuntos(0, 20),
            Notificacion::nuevaReponer({'s', 's', 's', 's', 'u'}),
            Notificacion::nuevaTurnoDe(1)
    });

    for (Nat j = 1; j < cantJugadores; j++) {
        compareNotificaciones(fachada.notificaciones(j), {
                Notificacion::nuevaUbicar(0, o),
                Notificacion::nuevaSumaPuntos(0, 20),
                Notificacion::nuevaTurnoDe(1)
        });
    }

};

TEST_F(JuegoGrandeTest, jugador_recibe_mal_ante_jugada_ilegitima_en_otro_eje) {
    /*
     * P A R A
     * O L
     * R T
     *   A
     */
    fachada.recibirMensaje(0, {{0, 0, 'p'}, {0, 1, 'o'}, {0, 2, 'r'}});
    fachada.recibirMensaje(1, {{1, 0, 'a'}, {2, 0, 'r'}, {3, 0, 'a'}});

    fachada.notificaciones(2);

    Ocurrencia o = {{1, 1, 'l'}, {1, 2, 't'}, {1, 3, 'a'}};
    fachada.recibirMensaje(2, o);

    compareNotificaciones(fachada.notificaciones(2), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoGrandeTest, jugadores_reciben_notificaciones_ante_jugada_cruzadas) {
    /*
     * P A R A
     * O
     * R
     */
    fachada.recibirMensaje(0, {{0, 0, 'p'}, {0, 1, 'o'}, {0, 2, 'r'}});

    // limpiar notifs
    fachada.notificaciones(0);
    fachada.notificaciones(1);
    fachada.notificaciones(2);

    Ocurrencia o = {{1, 0, 'a'}, {2, 0, 'r'}, {3, 0, 'a'}};
    fachada.recibirMensaje(1, o);



    compareNotificaciones(fachada.notificaciones(1), {
            Notificacion::nuevaUbicar(1, o),
            Notificacion::nuevaSumaPuntos(1, 9),
            Notificacion::nuevaReponer({'s', 'u', 'u'}),
            Notificacion::nuevaTurnoDe(2)
    });


    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaUbicar(1, o),
            Notificacion::nuevaSumaPuntos(1, 9),
            Notificacion::nuevaTurnoDe(2)
    });
    compareNotificaciones(fachada.notificaciones(2), {
            Notificacion::nuevaUbicar(1, o),
            Notificacion::nuevaSumaPuntos(1, 9),
            Notificacion::nuevaTurnoDe(2)
    });
};