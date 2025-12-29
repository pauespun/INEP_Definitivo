#include "PlanGo.hxx"

// Inicializamos el puntero estático
PlanGo* PlanGo::instance = nullptr;

PlanGo::PlanGo() {
    descompte = 0.20f; // Ejemplo: 20% descuento [cite: 41]
    usuariLoggejat = nullptr;
}

PlanGo& PlanGo::getInstance() {
    if (instance == nullptr) {
        instance = new PlanGo();
    }
    return *instance;
}

void PlanGo::iniciaSessio(std::shared_ptr<usuari> u) {
    usuariLoggejat = u;
}

void PlanGo::tancaSessio() {
    usuariLoggejat = nullptr;
}

std::shared_ptr<usuari> PlanGo::getUsuariLoggejat() {
    return usuariLoggejat;
}

bool PlanGo::hiHaUsuariLoggejat() {
    return usuariLoggejat != nullptr;
}

float PlanGo::get_descompte() const {
    return descompte;
}