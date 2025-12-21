#include "CtrlModificaUsuari.hxx"
#include "CtrlConsultaUsuari.hxx" // IMPORTANTE: Para reutilizar la consulta
#include "PlanGo.hxx"
#include "DAOUsuari.hxx"
#include "CtrlRegistraUsuari.hxx" // Para las excepciones (CorreuExisteix, MenorEdat)
#include <stdexcept>

// --- 1. CONSULTA (Reutilització) ---
DTOUsuari CtrlModificaUsuari::consultaUsuari() {
    // "Nota: reusem el consulta usuari del CtrlConsultaUsuari"
    CtrlConsultaUsuari ctrlConsulta;
    return ctrlConsulta.consultaUsuari();
}

// --- 2. MODIFICACIÓ ---
DTOUsuari CtrlModificaUsuari::modificaUsuari(const std::string& nom, const std::string& correu, int edat) {
    // A. Obtener usuario en memoria (Singleton)
    auto u_ptr = PlanGo::getInstance().getUsuariLoggejat();
    if (!u_ptr) throw std::runtime_error("No hi ha usuari loggejat");

    DAOUsuari dao;
    bool sHaModificat = false;

    // B. Aplicar Setters (Diagrama pasos 1-6)

    // Nom
    if (!nom.empty()) {
        u_ptr->set_nom(nom);
        sHaModificat = true;
    }

    // Correu (validamos duplicidad antes)
    if (!correu.empty() && correu != u_ptr->get_correuElectronic()) {
        if (dao.existeixEmail(correu)) {
            throw CorreuExisteix(); // Escenario alternativo: Correu existeix
        }
        u_ptr->set_correuElectronic(correu);
        sHaModificat = true;
    }

    // Edat
    if (edat != -1) {
        if (edat < 18) throw MenorEdat(); // Escenario alternativo: Menor edat
        u_ptr->set_edat(edat);
        sHaModificat = true;
    }

    // C. Guardar en BD (Diagrama paso 8)
    if (sHaModificat) {
        dao.modifica(*u_ptr);
    }

    // D. OBTENER INFORMACIÓN REAL DE LA BD (Diagrama pasos 9-10)
    // "Per confirmar que s’ha fet de manera correcta s’ha d’anar a la base de dades"

    std::string sobrenom = u_ptr->get_sobrenom(); // Paso 9
    usuari u_mod = dao.obte(sobrenom);            // Paso 10: Recarga desde BD

    // E. Retornar DTO (Paso 11)
    return u_mod.obtéInfo();
}