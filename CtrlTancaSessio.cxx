#include "CtrlTancaSessio.hxx"
#include "PlanGo.hxx"

void CtrlTancaSessio::tancaSessio() {
    // El controlador habla directamente con el Singleton de sesión
    PlanGo::getInstance().tancaSessio();
}