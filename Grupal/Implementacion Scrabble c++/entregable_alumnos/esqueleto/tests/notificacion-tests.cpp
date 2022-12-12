
#include "gtest-1.8.1/gtest.h"

#include "../src/Tipos.h"
#include "../src/Notificacion.h"


TEST(testsDeNotificacion, idClienteTraeId) {

    Notificacion n = Notificacion::nuevaIdCliente(34);

    EXPECT_EQ(n.tipoNotificacion(), TipoNotificacion::IdCliente);

    EXPECT_EQ(n.idCliente(), 34);
}

TEST(testsDeNotificacion, empezarTraeTamano) {

    Notificacion* n = new Notificacion(Notificacion::nuevaEmpezar(1220));

    EXPECT_EQ(n->tipoNotificacion(), TipoNotificacion::Empezar);

    EXPECT_EQ(n->empezar(), 1220);

    delete n;
}
