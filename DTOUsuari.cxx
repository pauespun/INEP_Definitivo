#include "DTOUsuari.hxx"

// Constructor para CONSULTAR (Sin contraseña, con reservas)
DTOUsuari::DTOUsuari(std::string sobrenom, std::string nom, std::string correu, int edat, int totalReserves)
    : _sobrenom(sobrenom), _nom(nom), _correuElectronic(correu), _edat(edat), _totalReserves(totalReserves)
{
    _contrasenya = ""; // No devolvemos la contraseña al consultar
}

// Constructor para REGISTRAR (Con contraseña, reservas a 0)
DTOUsuari::DTOUsuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat)
    : _sobrenom(sobrenom), _nom(nom), _correuElectronic(correu), _contrasenya(contra), _edat(edat)
{
    _totalReserves = 0;
}

// Getters
std::string DTOUsuari::get_sobrenom() const { return _sobrenom; }
std::string DTOUsuari::get_nom() const { return _nom; }
std::string DTOUsuari::get_correuElectronic() const { return _correuElectronic; }
std::string DTOUsuari::get_contrasenya() const { return _contrasenya; }
int DTOUsuari::get_edat() const { return _edat; }
int DTOUsuari::get_totalReserves() const { return _totalReserves; }