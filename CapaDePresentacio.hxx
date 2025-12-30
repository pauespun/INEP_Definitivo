#pragma once
#include <string>
#include "DTOUsuari.hxx"
#include "DTOExperiencia.hxx"
// Inclou aquí la teva classe de Domini si cal, o fes forward declaration
// #include "CapaDeDomini.hxx"

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
    void tancarSessio();

    // Operacions sobre l'usuari loguejat
    void consultarUsuari();
    void modificarUsuari();

    // Retorna true si s'ha esborrat correctament (per saber si hem de fer logout)
    bool esborrarUsuari();

    void reservarEscapada();
    void reservarActivitat();

    void consultarExperiencies();
    void visualitzarReserves();

    // Mètodes antics (llegir_usuaris, etc.) els pots mantenir si vols per debug,
    // però en l'aplicació final no se solen mostrar tots els usuaris.

private:
    CapaDePresentacio(); // Constructor privat

    // Aquí guardarem, per exemple, el "sobrenom" de l'usuari que ha iniciat sessió
    std::string usuariLoguejat;
};