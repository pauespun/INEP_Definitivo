#pragma once
#include <memory>
#include "usuari.hxx"

class PlanGo {
private:
    // Instancia única (Singleton)
    static PlanGo* instance;

    // Usuario actualmente logueado
    std::shared_ptr<usuari> usuariLoggejat;
    float descompte;

    // Constructor privado
    PlanGo();

public:
    // Método para obtener la instancia
    static PlanGo& getInstance();

    // Gestión de sesión
    void iniciaSessio(std::shared_ptr<usuari> u);
    void tancaSessio();

    // Getters y comprobaciones
    std::shared_ptr<usuari> getUsuariLoggejat();
    bool hiHaUsuariLoggejat();
    float get_descompte() const;
};
