#include "CtrlConsultaUsuari.hxx"
#include "PlanGo.hxx"
#include <stdexcept>

DTOUsuari CtrlConsultaUsuari::consultaUsuari() {
    // 1. Obtenemos el usuario de la sesión
    auto usuari_ptr = PlanGo::getInstance().getUsuariLoggejat();

    if (!usuari_ptr) {
        throw std::runtime_error("Error: No hi ha cap usuari loggejat.");
    }

    // 2. Delegamos en el usuario la creación de su propia info
    return usuari_ptr->obteInfo();
}