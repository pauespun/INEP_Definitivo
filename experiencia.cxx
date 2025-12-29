#include "experiencia.hxx"
#include "PlanGo.hxx"

experiencia::experiencia() {
    _num_reserves = 0;
}

experiencia::~experiencia() {
}

// Implementación Getters
std::string experiencia::get_nom() const {
    return _nom;
}

std::string experiencia::get_descripcio() const {
    return _descripcio;
}

std::string experiencia::get_ciutat() const {
    return _ciutat;
}

int experiencia::get_maxim_places() const {
    return _maxim_places;
}

float experiencia::get_preu() const {
    return _preu;
}

std::string experiencia::get_data_alta() const {
    return _data_alta;
}

int experiencia::get_num_reserves() const {
    return _num_reserves;
}

// Implementación Setters
void experiencia::set_nom(const std::string& n) {
    _nom = n;
}

void experiencia::set_descripcio(const std::string& d) {
    _descripcio = d;
}

void experiencia::set_ciutat(const std::string& c) {
    _ciutat = c;
}

void experiencia::set_maxim_places(int mp) {
    _maxim_places = mp;
}

void experiencia::set_preu(float p) {
    _preu = p;
}

void experiencia::set_data_alta(const std::string& da) {
    _data_alta = da;
}

void experiencia::set_num_reserves(int nr) {
    _num_reserves = nr;
}

float experiencia::calculaPreu(int nPersones, bool primeraRes) const {
    float preu = calculaPreu(nPersones); // polimórfico

    if (primeraRes) {
        float d = PlanGo::getInstance().get_descompte(); // d = 0.2
        preu = preu * (1.0f - d); // ✅ 0.8
    }
    return preu;
}
