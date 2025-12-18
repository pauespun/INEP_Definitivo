#include "usuari.hxx"
#include "DTOUsuari.hxx" // NECESARIO AQUÍ

// Constructor
usuari::usuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat)
    : _sobrenom(sobrenom), _nom(nom), _correuElectronic(correu), _contrasenya(contra), _edat(edat)
{
}

// Getters básicos
std::string usuari::get_sobrenom() const { return _sobrenom; }
std::string usuari::get_nom() const { return _nom; }
std::string usuari::get_correuElectronic() const { return _correuElectronic; }
std::string usuari::get_contrasenya() const { return _contrasenya; }
int usuari::get_edat() const { return _edat; }

// Comprobar contraseña
bool usuari::comprovaContrasenya(const std::string& contra) const {
    return _contrasenya == contra;
}

// IMPLEMENTACIÓN DE OBTÉ INFO
DTOUsuari usuari::obtéInfo() const {
    // 1. Calculamos reservas (Simulado a 0 porque no hay tabla reservas aún)
    int total = 0;

    // 2. Creamos y devolvemos el DTO usando el constructor de Consulta
    return DTOUsuari(_sobrenom, _nom, _correuElectronic, _edat, total);
}