#include "NotificacionesUtils.h"

void compareNotificaciones(const list<Notificacion>& lhs, const list<Notificacion>& rhs){
    EXPECT_EQ(lhs.size(), rhs.size());

    auto lhs_it = lhs.begin();
    auto rhs_it = rhs.begin();
    while(lhs_it != lhs.end()){
        EXPECT_EQ(lhs_it->tipoNotificacion(), rhs_it->tipoNotificacion());

        switch (lhs_it->tipoNotificacion()) {
            case TipoNotificacion::IdCliente:
                EXPECT_EQ(lhs_it->idCliente(), rhs_it->idCliente());
                break;
            case TipoNotificacion::Empezar:
                EXPECT_EQ(lhs_it->empezar(), rhs_it->empezar());
                break;
            case TipoNotificacion::TurnoDe:
                EXPECT_EQ(lhs_it->turnoDe(), rhs_it->turnoDe());
                break;
            case TipoNotificacion::Ubicar:
                EXPECT_EQ(lhs_it->ubicar(), rhs_it->ubicar());
                break;
            case TipoNotificacion::Reponer:
                EXPECT_EQ(lhs_it->reponer(), rhs_it->reponer());
                break;
            case TipoNotificacion::SumaPuntos:
                EXPECT_EQ(lhs_it->sumaPuntos(), rhs_it->sumaPuntos());
                break;
            case TipoNotificacion::Mal:
                break;}

        lhs_it++;
        rhs_it++;
    }
}
