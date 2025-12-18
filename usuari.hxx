// usuari.hxx
#pragma once
#include <odb/core.hxx>
#include <string>
#include "model.hxx"
#include "DTOUsuari.hxx"


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

    // --- NUEVO MÉTODO SEGÚN DIAGRAMA [cite: 154] ---
    // Retorna true si coincide, false si no.
    bool comprovaContrasenya(const std::string& contra) const;

    DTOUsuari obtéInfo() const;

private:
    friend class odb::access;
#pragma db id
    std::string _sobrenom;
    std::string _nom;
#pragma db type("VARCHAR(255)") unique
    std::string _correuElectronic;
    std::string _contrasenya;
#pragma db options("CHECK(edat >= 18)")
    int _edat;

    // CUANDO TENGAS RESERVAS, ESTO SERÁ ASÍ:
    // #pragma db value_not_null inverse(usuari_)
    // std::vector<std::shared_ptr<reserva>> _reserves;
};