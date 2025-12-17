// CapaDeDomini.hxx
#pragma once
#include <string>
#include <memory>
#include "DTOUsuari.hxx"

// Patró Singleton y Façana de Domini
class CapaDeDomini
{
public:
    // Mètode per obtenir la instància única
    static CapaDeDomini& getInstance();

    // Operacions CRUD adaptades al disseny PlanGo

    // Registrar: Ara demana correu, contrasenya i edat (int)
    void registrarUsuari(const std::string& sobrenom, const std::string& nom,
        const std::string& correu, const std::string& contra, int edat);

    // Consultar: Retorna un DTO per no exposar l'objecte de domini directament
    DTOUsuari consultarUsuari(const std::string& sobrenom);

    // Modificar: Permet canviar nom, correu i edat. 
    // Nota: Passem -1 a edat si no es vol modificar.
    void modificarUsuari(const std::string& sobrenom, const std::string& nou_nom,
        const std::string& nou_correu, int nova_edat);

    // Esborrar
    void esborrarUsuari(const std::string& sobrenom);

private:
    // Constructor privat (Singleton)
    CapaDeDomini() = default;

    // Evitem còpia i assignació
    CapaDeDomini(const CapaDeDomini&) = delete;
    CapaDeDomini& operator=(const CapaDeDomini&) = delete;
};