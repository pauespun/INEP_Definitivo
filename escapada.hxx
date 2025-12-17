#pragma once
#include "experiencia.hxx"
#include <odb/core.hxx>

#pragma db object
class Escapada : public Experiencia {
public:
    Escapada() = default;
    Escapada(string nom, string desc, string ciutat, int maxP, float preu, date data, string hotel, int numNits);

    string getTipus() const override { return "ESCAPADA"; }
    string getHotel() const;
    // ...

private:
    friend class odb::access;
    string _hotel;
    int _numNits;
};