#pragma once
#include <iostream>
#include <string>
#include "CapaDeDomini.hxx" // Inclou DTOUsuari

class CapaDePresentacio
{
public:
    // Patró Singleton
    static CapaDePresentacio& getInstance() {
        static CapaDePresentacio instance;
        return instance;
    }

    // Operacions de presentació
    void crear_usuari();
    void llegir_usuaris();
    void llegir_usuari();
    void actualitzar_usuari();
    void esborrar_usuari();

private:
    CapaDePresentacio() = default;

    // Evitar còpia
    CapaDePresentacio(const CapaDePresentacio&) = delete;
    CapaDePresentacio& operator=(const CapaDePresentacio&) = delete;
};