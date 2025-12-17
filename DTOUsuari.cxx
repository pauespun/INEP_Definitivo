// Archivo: DTOUsuari.cxx
#include "DTOUsuari.hxx"

// Constructor
DTOUsuari::DTOUsuari(std::string sobrenom, std::string nom, std::string correuElectronic, int edat)
    : _sobrenom(sobrenom), _nom(nom), _correuElectronic(correuElectronic), _edat(edat)
{
}

// Constructor auxiliar desde un objeto de dominio
DTOUsuari::DTOUsuari(const usuari& u)
	: _sobrenom(u.get_sobrenom()), _nom(u.get_nom()), _correuElectronic(u.get_correuElectronic()), _edat(u.get_edat())
{
}

// Getters (solo si no los definiste ya dentro del .hxx)
std::string DTOUsuari::get_sobrenom() const {
    return _sobrenom;
}

std::string DTOUsuari::get_nom() const {
    return _nom;
}

std::string DTOUsuari::get_correuElectronic() const {
    return _correuElectronic;
}

int DTOUsuari::get_edat() const {
    return _edat;
}