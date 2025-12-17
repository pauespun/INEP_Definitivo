#pragma once
#include <odb/core.hxx>
#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "model.hxx"
#include "usuari.hxx"
#include "experiencia.hxx"

using namespace std;
using namespace boost::gregorian;

#pragma db object
class Reserva {
public:
    Reserva() = default;
    // Constructor con punteros a los objetos relacionados
    Reserva(date data, int numPlaces, float preuPagat, shared_ptr<usuari> u, shared_ptr<Experiencia> e);

    // Getters para navegar por la relación
    shared_ptr<usuari> getUsuari() const;
    shared_ptr<Experiencia> getExperiencia() const;

private:
    friend class odb::access;

#pragma db id auto
    unsigned long _id; // ID autoincremental

    date _data;
    int _numPlaces;
    float _preuPagat;

    // Relación N:1 con Usuari (Una reserva es de un usuario)
#pragma db not_null
    shared_ptr<usuari> _usuari;

    // Relación N:1 con Experiencia (Una reserva es de una experiencia)
#pragma db not_null
    shared_ptr<Experiencia> _experiencia;
};