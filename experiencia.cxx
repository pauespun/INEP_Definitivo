#include "experiencia.hxx"

Experiencia::Experiencia(string nom, string descripcio, string ciutat, int maximPlaces, float preu, date dataAlta)
    : _nom(nom), _descripcio(descripcio), _ciutat(ciutat), _maximPlaces(maximPlaces), _preu(preu), _dataAlta(dataAlta) {
}

string Experiencia::getNom() const { return _nom; }
string Experiencia::getDescripcio() const { return _descripcio; }
// ... implementa el resto