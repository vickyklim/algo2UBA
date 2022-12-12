#ifndef TP_JUEGODEPALABRAS_SERVIDOR_H
#define TP_JUEGODEPALABRAS_SERVIDOR_H

#include "Notificacion.h"
#include <queue>
#include "Juego.h"


class Servidor {
public:

    Servidor(
        Nat clientesEsperados,
        Variante variante,
        const queue<Letra> r);

    IdCliente conectarCliente();

    void enviarMensaje(IdCliente id, const Ocurrencia& o);

    queue<Notificacion> consultarCola(IdCliente id);

    Nat clientesEsperados();

    Nat clientesConectados();



private:
    Nat _clientesEsperados;
    Nat _clientesConectados;
    Juego _juego;
    tuple<Variante,queue<Letra>> _configuracion;
    vector<queue<tuple<Notificacion,Nat>>> _notificacionesInd;
    vector<tuple<Notificacion,Nat>> _notificacionesGen;
    vector<Nat> _iterador;
    Nat _contador;

};

#endif // SERVIDOR_H

