#include "Servidor.h"
#include "Notificacion.h"
#include <queue>
#include "auxiliares.h"


Servidor::Servidor(Nat clientesEsperados, Variante variante, const queue<Letra> r):
_clientesEsperados(clientesEsperados), _configuracion(make_tuple(variante,r)), _clientesConectados(0),
_juego(clientesEsperados,variante,r), _notificacionesGen(), _notificacionesInd(), _iterador(), _contador(0){};




IdCliente Servidor::conectarCliente() {
    _clientesConectados = _clientesConectados + 1;
    std::queue<tuple<Notificacion,Nat>> vacia;
    _notificacionesInd.push_back(vacia); //creemos que agrega una cola vacia, VER
    _notificacionesInd[_clientesConectados-1].push(make_tuple(Notificacion::nuevaIdCliente(_clientesConectados-1),_contador));
    _contador = _contador+1; //ver que onda lo de Notificacion::
    _iterador.push_back(0);
    if(_clientesConectados==_clientesEsperados){
        _notificacionesGen.push_back(make_tuple(Notificacion::nuevaEmpezar(_juego.tamanoTablero()),_contador));
        _contador = _contador +1;
        _notificacionesGen.push_back(make_tuple(Notificacion::nuevaTurnoDe(_juego.turno()), _contador));
        _contador++;
        for(int i=0; i<_clientesConectados; i++){
            _notificacionesInd[i].push(make_tuple(Notificacion::nuevaReponer(colaAMultiset(proximosN(get<1>(_configuracion), _juego.verVariante().cantFichas()))),_contador));
            _contador=_contador+1;
        }
    }
    return _clientesConectados-1;
}


void Servidor::enviarMensaje(IdCliente id, const Ocurrencia &o) {
    if (_juego.jugadaValida(o) && _juego.turno() == id && _clientesConectados == _clientesEsperados) {
        _juego.ubicarFichas(o);
        _notificacionesGen.push_back(make_tuple(Notificacion::nuevaUbicar(id, o), _contador));
        _contador++;
        _notificacionesGen.push_back(
                make_tuple(Notificacion::nuevaSumaPuntos(id, _juego.obtenerPuntaje(_juego.turno()-1%_clientesEsperados)), _contador));
        _contador++;
        _notificacionesInd[id].push(
                make_tuple(Notificacion::nuevaReponer(colaAMultiset(proximosN(get<1>(_configuracion), o.size()))),
                           _contador));
        _contador++;
        _notificacionesGen.push_back(make_tuple(Notificacion::nuevaTurnoDe(_juego.turno()), _contador));
        _contador++;


    } else {
        _notificacionesInd[id].push(make_tuple(Notificacion::nuevaMal(), _contador));
        _contador++;
    }
}

queue<Notificacion> Servidor::consultarCola(IdCliente id) {
    Nat n = _notificacionesInd[id].size() + _notificacionesGen.size() - _iterador[id];
    queue<Notificacion> res; //asumimos lo inicializa vacio
    for(int i=0; i<n; i++) {
        if (_notificacionesGen.size()<=_iterador[id] or (_notificacionesInd[id].size()>0 and _notificacionesGen.size()>0 and get<1>(_notificacionesInd[id].front()) < get<1>(_notificacionesGen[_iterador[id]]))) {
            res.push(get<0>(_notificacionesInd[id].front()));
            _notificacionesInd[id].pop();
        } else {
            res.push(get<0>(_notificacionesGen[_iterador[id]]));
            _iterador[id]++;
        }
    }
    return res;
}


Nat Servidor::clientesConectados() {
    return _clientesConectados;
}

Nat Servidor::clientesEsperados() {
    return _clientesEsperados;
}


