#include "escapada.hxx"
#include "PlanGo.hxx"

escapada::escapada() {
}

escapada::escapada(const std::string& nom, const std::string& desc, const std::string& ciutat,
    int max_places, float preu, const std::string& data,
    const std::string& hotel, int nits)
{
    // Usamos los setters de la clase padre o asignamos directamente si tenemos acceso (protected)
    // Al ser protected en experiencia.hxx, podemos acceder a _nom, etc.
    _nom = nom;
    _descripcio = desc;
    _ciutat = ciutat;
    _maxim_places = max_places;
    _preu = preu;
    _data_alta = data;
    _num_reserves = 0;

    _hotel = hotel;
    _num_nits = nits;
}

escapada::~escapada() {
}

std::string escapada::get_hotel() const {
    return _hotel;
}

int escapada::get_num_nits() const {
    return _num_nits;
}

void escapada::set_hotel(const std::string& h) {
    _hotel = h;
}

void escapada::set_num_nits(int n) {
    _num_nits = n;
}

float escapada::calculaPreu(int nPersones, bool primeraRes) {
    // Lógica: En escapada el precio suele ser fijo por el pack, 
    // pero si quieres multiplicar por personas, hazlo aquí.
    // Según tu diagrama, usamos el precio base.

    float preu_final = this->get_preu();

    if (primeraRes) {
        float descompte = PlanGo::getInstance().get_descompte();
        preu_final = preu_final * (1.0f - descompte);
    }
    return preu_final;
}