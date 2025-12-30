#include "CtrlModificaUsuari.hxx"
#include "CtrlConsultaUsuari.hxx" 
#include "PlanGo.hxx"
#include "DAOUsuari.hxx"
#include "CtrlRegistraUsuari.hxx" 
#include <stdexcept>

// --- 1. CONSULTA (Reutilització) ---
DTOUsuari CtrlModificaUsuari::consultaUsuari() {
    CtrlConsultaUsuari ctrlConsulta;
    return ctrlConsulta.consultaUsuari();
}

// --- 2. MODIFICACIÓ ---
DTOUsuari CtrlModificaUsuari::modificaUsuari(const std::string& nom, const std::string& correu, int edat) {
    auto u_ptr = PlanGo::getInstance().getUsuariLoggejat();
    if (!u_ptr) throw std::runtime_error("No hi ha usuari loggejat");

    DAOUsuari dao;
    bool sHaModificat = false;

    // --- 1. FASE DE VALIDACIÓ (Lectura només) ---

    // Validem correu duplicat ABANS de canviar res
    if (!correu.empty() && correu != u_ptr->get_correuElectronic()) {
        if (dao.existeixEmail(correu)) {
            // Si salta això, l'objecte usuari encara està intacte. Correcte.
            throw CorreuExisteix();
        }
    }

    // Validem edat ABANS de canviar res
    if (edat != -1) {
        if (edat < 18) {
            throw MenorEdat();
        }
    }

    // --- 2. FASE DE MODIFICACIÓ (Escriptura) ---
    // Si arribem aquí, és segur aplicar els canvis.

    if (!nom.empty()) {
        u_ptr->set_nom(nom);
        sHaModificat = true;
    }

    if (!correu.empty() && correu != u_ptr->get_correuElectronic()) {
        u_ptr->set_correuElectronic(correu);
        sHaModificat = true;
    }

    if (edat != -1) {
        u_ptr->set_edat(edat);
        sHaModificat = true;
    }

    // --- 3. PERSISTÈNCIA ---
    if (sHaModificat) {
        dao.modifica(*u_ptr);
    }

    // Recarreguem de BD per confirmar i retornar DTO
    std::string sobrenom = u_ptr->get_sobrenom();
    usuari u_mod = dao.obte(sobrenom);

    return u_mod.obteInfo();
}