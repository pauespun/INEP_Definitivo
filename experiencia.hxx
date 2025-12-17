#pragma once
#pragma once
#include <odb/core.hxx>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "model.hxx" // Importante

using namespace std;
using namespace boost::gregorian;

#pragma db object polymorphic
class Experiencia {
public:
    Experiencia() = default;
    Experiencia(string nom, string descripcio, string ciutat, int maximPlaces, float preu, date dataAlta);
    virtual ~Experiencia() = default; // Destructor virtual obligatorio para polimorfismo

    // Getters
    string getNom() const;
    string getDescripcio() const;
    // ... resto de getters

    // Método virtual puro para obligar a las hijas a implementarlo (opcional, pero buena práctica)
    virtual string getTipus() const = 0;

private:
    friend class odb::access;

#pragma db id
    string _nom; // El diseño marca "nom" como ID

    string _descripcio;
    string _ciutat;
    int _maximPlaces;
    float _preu;
    date _dataAlta; // Requiere perfil boost en compilación
    int _numReserves = 0; // Inicializado a 0
};