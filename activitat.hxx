#pragma once
#include "experiencia.hxx"
#include <odb/core.hxx>

#pragma db object
class Activitat : public Experiencia {
public:
    Activitat() = default;
    Activitat(string nom, string desc, string ciutat, int maxP, float preu, date data, int durada);

    string getTipus() const override { return "ACTIVITAT"; }
    int getDurada() const;

private:
    friend class odb::access;
    int _durada; // En minutos o horas según diseño
};