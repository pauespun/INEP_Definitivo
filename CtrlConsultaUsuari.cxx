#include "CtrlConsultaUsuari.hxx"
#include "PlanGo.hxx"
#include "DAOReserva.hxx" 
#include <stdexcept>


DTOUsuari CtrlConsultaUsuari::consultaUsuari() {
    // 1. Obtenim l'usuari de la sessió (Singleton)
    auto u = PlanGo::getInstance().getUsuariLoggejat();

    if (!u) {
        throw std::runtime_error("Error: No hi ha cap usuari loggejat.");
    }
    DAOReserva dao;
    auto llistaReserves = dao.obteReservesUsuari(u->get_sobrenom());
    int totalReserves = llistaReserves.size();

    // 3. Construïm el DTO manualment amb les dades correctes
    // Així ens assegurem que el número és el real.
    return DTOUsuari(
        u->get_sobrenom(),
        u->get_nom(),
        u->get_correuElectronic(),
        u->get_edat(),
        totalReserves
    );
}