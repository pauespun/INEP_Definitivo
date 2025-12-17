// usuari.hxx
#pragma once
#include <odb/core.hxx>
#include <string>
#include "model.hxx" // Importante incluir el modelo


#pragma db object
class usuari
{
public:
    usuari() = default;
    usuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat);

    // Getters
    std::string get_sobrenom() const;
    std::string get_nom() const;
    std::string get_correuElectronic() const;
    std::string get_contrasenya() const;
    int get_edat() const;

    // Setters
    void set_nom(std::string nom);
    void set_correuElectronic(std::string correu);
    void set_contrasenya(std::string contra);
    void set_edat(int edat);

private:
    friend class odb::access;

#pragma db id
    std::string _sobrenom; // ID según diseño

    std::string _nom;

    // RIT2: El correo debe ser único. ODB requiere definir el tamaño para índices únicos en MySQL/MariaDB
#pragma db type("VARCHAR(255)") unique
    std::string _correuElectronic;

    std::string _contrasenya;

    // RIT1: Edad >= 18
#pragma db options("CHECK(edat >= 18)")
    int _edat;
};