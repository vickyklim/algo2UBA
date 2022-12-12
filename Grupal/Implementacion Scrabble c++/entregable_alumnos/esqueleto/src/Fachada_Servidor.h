#ifndef FACHADA_SERVIDOR_H
#define FACHADA_SERVIDOR_H

#include "Letra.h"
#include "Notificacion.h"
#include "Fachada_Variante.h"
#include "Servidor.h"


class Fachada_Servidor {
public:
    /**
     * El constructor de Fachada_Servidor debe inicializar un nuevo servidor, y todas sus dependencias (como el juego,
     * la variante, el tablero, etc)
     *
     * Complejidad: O(tamanoTab**2 + TAMANIO_ALFABETO*cantJugadores + cantFichas*cantJugadores)
     */
    Fachada_Servidor(
        Nat cantJugadores,
        const Fachada_Variante& variante,
        const Repositorio& r
    ): _servidor(cantJugadores, variante.devolverVariante(), pasarAQueue(r)){};

    /**
     * Conecta un cliente al servidor y retorna su id de cliente
     *
     * Complejidad: O(1)
     */
    IdCliente conectarCliente(){
        _servidor.conectarCliente();
    };

    /**
     * Recibe un mensaje o del cliente id
     *
     * Complejidad: No se impone una cota explícita. La complejidad no debe depender de
     * N ni de K. Puede depender de |Σ|, F, Lmáx y del número de fichas que el jugador pretenda ubicar al
     * enviar este mensaje.
     */
    void recibirMensaje(IdCliente id, const Ocurrencia& o){
        _servidor.enviarMensaje(id,o);
    }

    /**
     * Retorna la cantidad de jugadores necesarios para poder empezar el juego
     *
     * Complejidad: O(1)
     */
    Nat jugadoresEsperados(){
        return _servidor.clientesEsperados();
    }

    /**
     * Retorna la cantidad de jugadores neonectadoscesarios para poder empezar el juego
     *
     * Complejidad: O(1)
     */
    Nat jugadoresConectados(){
        return _servidor.clientesConectados();
    };

    /**
     * Consulta y vacia la cola de notificaciones del cliente id
     *
     * Complejidad: O(n*F)
     *   donde n es la cantidad de mensajes sin consultar de dicho cliente
     *   y F es la cantidad de fichas por jugador de la variante.
     */
    std::list<Notificacion> notificaciones(IdCliente id){
        return pasarALista(_servidor.consultarCola(id));
    };

private:
    Servidor _servidor;
};

#endif // FACHADA_SERVIDOR_H

