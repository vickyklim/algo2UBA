#include "Notificacion.h"

Notificacion::Notificacion(TipoNotificacion t): _tipoNotificacion(t) {}

Notificacion Notificacion::nuevaIdCliente(IdCliente id) {
    Notificacion n {TipoNotificacion::IdCliente};
    n._idCliente = id;
    return n;
}

Notificacion Notificacion::nuevaEmpezar(Nat n2) {
    Notificacion n {TipoNotificacion::Empezar};
    n._empezar = n2;
    return n;
}

Notificacion Notificacion::nuevaTurnoDe(IdCliente id) {
    Notificacion n {TipoNotificacion::TurnoDe};
    n._turnoDe = id;
    return n;
}

Notificacion Notificacion::nuevaUbicar(IdCliente id, Ocurrencia oc) {
    Notificacion n {TipoNotificacion::Ubicar};
    n._ubicar = make_tuple(id, oc);
    return n;
}

Notificacion Notificacion::nuevaReponer(multiset<Letra> letras) {
    Notificacion n {TipoNotificacion::Reponer};
    n._reponer = letras;
    return n;
}

Notificacion Notificacion::nuevaSumaPuntos(IdCliente id, Nat puntos) {
    Notificacion n {TipoNotificacion::SumaPuntos};
    n._sumaPuntos = make_tuple(id, puntos);
    return n;
}

Notificacion Notificacion::nuevaMal() {
    Notificacion n {TipoNotificacion::Mal};
    return n;
}

TipoNotificacion Notificacion::tipoNotificacion() const {
    return _tipoNotificacion;
}

IdCliente Notificacion::idCliente() const {
    return _idCliente;
}

Nat Notificacion::empezar() const {
    return _empezar;
}

IdCliente Notificacion::turnoDe() const {
    return _turnoDe;
}

std::tuple<IdCliente, Ocurrencia> Notificacion::ubicar() const {
    return _ubicar;
}

multiset<Letra> Notificacion::reponer() const {
    return _reponer;
}

std::tuple<IdCliente, Nat> Notificacion::sumaPuntos() const {
    return _sumaPuntos;
}

bool Notificacion::operator==(const Notificacion &rhs) const{
    return _tipoNotificacion == rhs._tipoNotificacion
        && _idCliente == rhs._idCliente
        && _empezar == rhs._empezar
        && _turnoDe == rhs._turnoDe
        && _ubicar == rhs._ubicar
        && _reponer == rhs._reponer
        && _sumaPuntos == rhs._sumaPuntos
        ;
}

