#pragma once
#include <string>
#include "usuari.hxx"
#include <vector>

class DTOUsuari {
public:
    DTOUsuari() = default;
    DTOUsuari(std::string sobrenom, std::string nom, std::string correu, int edat);
    // Constructor auxiliar desde un objeto de dominio
    DTOUsuari(const usuari& u);
    std::vector<usuari> tots(); // O el nombre que estés intentando llamar
    std::string get_sobrenom() const;
    std::string get_nom() const;
    std::string get_correuElectronic() const;
    int get_edat() const;

private:
    std::string _sobrenom;
    std::string _nom;
    std::string _correuElectronic;
    int _edat;
};