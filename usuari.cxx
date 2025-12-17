#include "usuari.hxx"

usuari::usuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat)
	: _sobrenom(sobrenom), _nom(nom), _correuElectronic(correu), _contrasenya(contra), _edat(edat) {
}

std::string usuari::get_sobrenom() const { return _sobrenom; }
std::string usuari::get_nom() const { return _nom; }
std::string usuari::get_correuElectronic() const { return _correuElectronic; }
std::string usuari::get_contrasenya() const { return _contrasenya; }
int usuari::get_edat() const { return _edat; }

void usuari::set_nom(std::string nom) { _nom = nom; }
void usuari::set_correuElectronic(std::string correu) { _correuElectronic = correu; }
void usuari::set_contrasenya(std::string contra) { _contrasenya = contra; }
void usuari::set_edat(int edat) { _edat = edat; }