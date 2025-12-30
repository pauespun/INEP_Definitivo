#include "usuari.hxx"
#include "DTOUsuari.hxx"
#include "reserva.hxx"
#include "connexioBD.hxx"
#include "Excepcions.hxx"
#include "DAOReserva.hxx"

#include "usuari-odb.hxx"
#include "reserva-odb.hxx"
#include "experiencia-odb.hxx"

// Constructor
usuari::usuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat)
    : _sobrenom(sobrenom), _nom(nom), _correuElectronic(correu), _contrasenya(contra), _edat(edat)
{
}

// Getters
std::string usuari::get_sobrenom() const { return _sobrenom; }
std::string usuari::get_nom() const { return _nom; }
std::string usuari::get_correuElectronic() const { return _correuElectronic; }
std::string usuari::get_contrasenya() const { return _contrasenya; }
int usuari::get_edat() const { return _edat; }

// Setters
void usuari::set_nom(std::string nom) { _nom = nom; }
void usuari::set_correuElectronic(std::string correu) { _correuElectronic = correu; }
void usuari::set_edat(int edat) { _edat = edat; }

// Password
bool usuari::comprovaContrasenya(const std::string& contra) const {
    return _contrasenya == contra;
}

// Info
DTOUsuari usuari::obteInfo() const {
    return DTOUsuari(_nom, _sobrenom, _correuElectronic, _edat, _reserves.size());
}

// Reserves
std::vector<std::shared_ptr<reserva>>& usuari::get_reserves() { return _reserves; }
void usuari::set_reserves(const std::vector<std::shared_ptr<reserva>>& r) { _reserves = r; }

// Caso Escapada (places = maxim_places)
float usuari::afegirReserva(std::shared_ptr<experiencia> e) {
    auto db = connexioBD::getInstance().getDB();

    bool esPrimera = get_reserves().empty();
    int places = e->get_maxim_places();

    float preu_final = e->calculaPreu(places, esPrimera);

    std::shared_ptr<reserva> r(new reserva(shared_from_this(), e, places, preu_final));
    db->persist(r);

    _reserves.push_back(r);
    db->update(shared_from_this());

    e->set_num_reserves(e->get_num_reserves() + 1);
    db->update(e);

    return preu_final;
}

float usuari::calculaPreuReserva(std::shared_ptr<experiencia> e, int numPersones) const
{
    if (!e) throw std::runtime_error("Experiencia nula");
    if (numPersones < 1) throw std::invalid_argument("numPersones ha de ser >= 1");

    // Instanciamos el DAO (o lo pasamos por inyección si fuéramos muy puristas, 
    // pero instanciarlo aquí es aceptable en este diseño).
    DAOReserva dao;

    // 1. COMPROBAR CAPACIDAD (Usando el DAO)
    int ocupades = dao.placesOcupades(e->get_nom());

    if (ocupades + numPersones > e->get_maxim_places()) {
        throw std::runtime_error("Error: No hi ha places suficients disponibles.");
    }

    // 2. COMPROBAR DESCUENTO (Usando el DAO)
    // Si 'teAlgunaReserva' es true, NO es la primera reserva.
    bool teReserves = dao.teAlgunaReserva(_sobrenom);
    bool esPrimera = !teReserves; // Es primera si NO tiene reservas

    // 3. CALCULAR
    return e->calculaPreu(numPersones, esPrimera);
}


float usuari::afegirReserva(std::shared_ptr<experiencia> e, int numPersones) {
    auto db = connexioBD::getInstance().getDB();

    float preu_final = calculaPreuReserva(e, numPersones);

    std::shared_ptr<reserva> r(
        new reserva(shared_from_this(), e, numPersones, preu_final)
    );

    db->persist(r);

    _reserves.push_back(r);
    db->update(shared_from_this());

    e->set_num_reserves(e->get_num_reserves() + 1);
    db->update(e);

    return preu_final;
}
