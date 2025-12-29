#include "CtrlReservaEscapada.hxx"
#include "DAOEscapada.hxx"
#include "PlanGo.hxx"
#include "connexioBD.hxx"
#include <odb/transaction.hxx>
#include <stdexcept>

// Ya no necesitamos reserva-odb.hxx ni usuari-odb.hxx aquí, 
// porque el controlador ya no hace persist/update directo.
// Solo necesitamos acceso a BD para la transacción.

CtrlReservaEscapada::CtrlReservaEscapada() {}

DTOExperiencia CtrlReservaEscapada::consulta_escapada(const std::string& nom_escapada) {
    DAOEscapada dao;
    _escapada_actual = dao.obte(nom_escapada);

    DTOExperiencia dto(
        _escapada_actual->get_nom(),
        _escapada_actual->get_descripcio(),
        _escapada_actual->get_ciutat(),
        _escapada_actual->get_maxim_places(),
        _escapada_actual->get_preu(),
        _escapada_actual->get_hotel(),
        _escapada_actual->get_num_nits(),
        0
    );
    return dto;
}

float CtrlReservaEscapada::reserva_escapada() {
    using namespace odb::core;

    // 1. OBTENER USUARIO
    std::shared_ptr<usuari> u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("Error: No hi ha cap usuari loguejat.");

    // 2. OBTENER CONEXIÓN PARA TRANSACCIÓN
    auto db = connexioBD::getInstance().getDB();

    // Iniciamos transacción aquí para que todo lo que haga el usuario sea atómico
    transaction t(db->begin());

    // 3. DELEGACIÓN (Aquí está la clave del diagrama)
    // El controlador dice: "Usuario, añádete esta reserva".
    // Toda la lógica de precio, creación y persistencia ocurre dentro de 'afegirReserva'.
    float preu_final = u->afegirReserva(_escapada_actual);

    t.commit();

    return preu_final;
}