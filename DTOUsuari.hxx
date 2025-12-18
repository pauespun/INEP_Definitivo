#pragma once
#include <string>

class DTOUsuari {
public:
    DTOUsuari() = default;

    // CONSTRUCTOR PARA CONSULTA (Recibe el total de reservas calculado)
    DTOUsuari(std::string sobrenom, std::string nom, std::string correu, int edat, int totalReserves);

    // CONSTRUCTOR PARA REGISTRO (Recibe contraseña)
    DTOUsuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat);

    // Getters
    std::string get_sobrenom() const;
    std::string get_nom() const;
    std::string get_correuElectronic() const;
    std::string get_contrasenya() const;
    int get_edat() const;
    int get_totalReserves() const;

private:
    std::string _sobrenom;
    std::string _nom;
    std::string _correuElectronic;
    std::string _contrasenya;
    int _edat;
    int _totalReserves; // Atributo solo para mostrar en pantalla
};