#pragma once
#include <string>
#include "DTOUsuari.hxx"
#include "DTOExperiencia.hxx"

class CapaDePresentacio {
public:
    // Singleton
    static CapaDePresentacio& getInstance();

    // --- GESTIÓ SESSIÓ I USUARIS ---

    // Retorna true si el login és correcte
    bool iniciarSessio();

    // Registra un nou usuari
    void registrarUsuari();

    // Tanca la sessió (neteja variables)
    bool tancarSessio();

    // Operacions sobre l'usuari loguejat
    void consultarUsuari();
    void modificarUsuari();

    // Retorna true si s'ha esborrat correctament (per saber si hem de fer logout)
    bool esborrarUsuari();

    void reservarEscapada();
    void reservarActivitat();

    void consultarExperiencies();
    void visualitzarReserves();


private:
    CapaDePresentacio(); // Constructor privat

    // Aquí guardarem, per exemple, el "sobrenom" de l'usuari que ha iniciat sessió
    std::string usuariLoguejat;
};