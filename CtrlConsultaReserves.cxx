#include "CtrlConsultaReserves.hxx"
#include "DAOReserva.hxx"
#include "PlanGo.hxx"
#include "reserva.hxx"
#include <stdexcept>

CtrlConsultaReserves::CtrlConsultaReserves() {}

DTOReserves CtrlConsultaReserves::consultaReserves() {
    // 1. Obtenim usuari
    auto u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("No hi ha usuari loguejat.");

    // 2. Obtenim entitats del DAO
    DAOReserva dao;
    auto llistaEntitats = dao.obteReservesUsuari(u->get_sobrenom());

    // 3. Creem el contenidor buit
    DTOReserves resultat;

    // 4. LOOP (Tal com diu el diagrama)
    for (auto& r : llistaEntitats) {
        // Obtenim el DTO singular de la reserva
        DTOReserva dto = r->obteInfo();

        // L'afegim al contenidor (que sumarà el preu internament)
        resultat.afegirReserva(dto);
    }

    // Retornem el contenidor ple i amb el total calculat
    return resultat;
}