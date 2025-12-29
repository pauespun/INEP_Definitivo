#include "CtrlReservaActivitat.hxx"
#include "DAOActivitat.hxx"
#include "PlanGo.hxx"
#include "connexioBD.hxx"
#include <odb/transaction.hxx>
#include <stdexcept>

CtrlReservaActivitat::CtrlReservaActivitat() {}

DTOExperiencia CtrlReservaActivitat::consulta_activitat(const std::string& nom_activitat) {
    DAOActivitat dao;
    _activitat_actual = dao.obte(nom_activitat);

    DTOExperiencia dto(
        _activitat_actual->get_nom(),
        _activitat_actual->get_descripcio(),
        _activitat_actual->get_ciutat(),
        _activitat_actual->get_maxim_places(),
        _activitat_actual->get_preu(),
        "",      // hotel (no aplica)
        0,       // nits (no aplica)
        _activitat_actual->get_durada() // durada en minuts
    );

    return dto;
}

/*float CtrlReservaActivitat::preu_total(int numPersones) const {
    if (!_activitat_actual)
        throw std::runtime_error("Error: No hi ha cap activitat consultada.");

    if (numPersones < 1)
        throw std::invalid_argument("Error: El nombre de persones ha de ser >= 1.");

    if (numPersones > _activitat_actual->get_maxim_places())
        throw std::invalid_argument("Error: El nombre de persones supera el maxim.");

    // Preu per persona * num persones
    return _activitat_actual->get_preu() * numPersones;
}*/

float CtrlReservaActivitat::preu_total(int numPersones) const {
    if (!_activitat_actual)
        throw std::runtime_error("Error: No hi ha cap activitat consultada.");

    auto u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("Usuari no loguejat");

    return u->calculaPreuReserva(_activitat_actual, numPersones);
}




float CtrlReservaActivitat::reserva_activitat(int numPersones) {
    using namespace odb::core;

    if (!_activitat_actual)
        throw std::runtime_error("Error: No hi ha cap activitat consultada.");

    if (numPersones < 1)
        throw std::invalid_argument("Error: El nombre de persones ha de ser >= 1.");

    std::shared_ptr<usuari> u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("Error: No hi ha cap usuari loguejat.");

    auto db = connexioBD::getInstance().getDB();
    transaction t(db->begin());

    // ⚠️ esto solo funcionará si tienes la sobrecarga en usuari:
    float preu_final = u->afegirReserva(_activitat_actual, numPersones);

    t.commit();
    return preu_final;
}

