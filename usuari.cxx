#include "usuari.hxx"
#include "DTOUsuari.hxx" // NECESARIO AQUÍ
#include <vector>
#include "reserva.hxx"
#include "connexioBD.hxx"

#include "usuari-odb.hxx"     // Para db->update(shared_from_this())
#include "reserva-odb.hxx"    // Para db->persist(r)
#include "experiencia-odb.hxx"// Para db->update(e)

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
DTOUsuari usuari::obteInfo() const {
    // Calculamos el total de reservas usando el vector
    return DTOUsuari(_nom, _sobrenom, _correuElectronic, _edat, _reserves.size());
}

void usuari::set_nom(std::string nom) {
    this->_nom = nom;
}

void usuari::set_correuElectronic(std::string correu) {
    this->_correuElectronic = correu;
}

void usuari::set_edat(int edat) {
    this->_edat = edat;
}


std::vector<std::shared_ptr<reserva>>& usuari::get_reserves() {
    return _reserves;
}

void usuari::set_reserves(const std::vector<std::shared_ptr<reserva>>& r) {
    _reserves = r;
}

float usuari::afegirReserva(std::shared_ptr<experiencia> e) {
    // Obtener conexión
    auto db = connexioBD::getInstance().getDB();

    // 1. Datos para cálculo
    bool esPrimera = get_reserves().empty();
    int places = e->get_maxim_places();

    // 2. Delegar cálculo de precio a Experiencia
    float preu_final = e->calculaPreu(places, esPrimera);

    // 3. Crear Reserva (usamos shared_from_this() para pasarnos a nosotros mismos)
    std::shared_ptr<reserva> r(new reserva(shared_from_this(), e, places, preu_final));

    // 4. Persistencia (Simulando el DAOReserva::inserta(r))
    db->persist(r);

    // 5. Actualizar relaciones
    _reserves.push_back(r);
    db->update(shared_from_this()); // Actualizamos usuario

    e->set_num_reserves(e->get_num_reserves() + 1);
    db->update(e); // Actualizamos experiencia

    return preu_final;
}