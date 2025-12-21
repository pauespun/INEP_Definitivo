#include "CtrlEsborrarUsuari.hxx"
#include "PlanGo.hxx"
#include "DAOUsuari.hxx"
#include <stdexcept>


void CtrlEsborrarUsuari::esborrarUsuari(const std::string& contrasenya) {
    // 1. Obtener usuario logueado
    auto u_ptr = PlanGo::getInstance().getUsuariLoggejat();

    // Precondición: Existe usuario logueado
    if (!u_ptr) {
        throw std::runtime_error("No hi ha cap usuari loggejat.");
    }

    // 2. VERIFICAR CONTRASENYA
    // Usamos el método que ya creamos en la clase Usuari
    if (!u_ptr->comprovaContrasenya(contrasenya)) {
        throw ErrorContrasenya(); // Excepción especificada en el diseño
    }

    // 3. Borrar de la Base de Datos
    // "No cal incloure l'esborrat de les reserves perquè ho farà el SGDB (ON DELETE CASCADE)"
    DAOUsuari dao;
    dao.esborra(u_ptr->get_sobrenom());

    // 4. Tancar la sessió
    // "Una vegada esborrat l'usuari es tanca la sessió"
    PlanGo::getInstance().tancaSessio();
}