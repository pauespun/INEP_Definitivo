#ifndef RESERVA_HXX
#define RESERVA_HXX

#include <memory>
#include <string>
#include <odb/core.hxx>

#include "usuari.hxx"     
#include "experiencia.hxx"  
#include "DTOReserva.hxx"

class usuari;
class experiencia;

#pragma db object table("reserva")
class reserva {
public:
    reserva(std::shared_ptr<usuari> u, std::shared_ptr<experiencia> e, int places, float pagat);

    virtual ~reserva();

    // Getters
    unsigned int get_id() const;
    std::string get_data() const;
    int get_num_places() const;
    float get_preu_pagat() const;
    std::shared_ptr<usuari> get_usuari() const;
    std::shared_ptr<experiencia> get_experiencia() const;

    // Setters
    void set_data(const std::string& d);
    // Normalmente no cambiamos ID, usuario o experiencia de una reserva ya creada, 
    // pero puedes añadirlos si los necesitas.

    DTOReserva obteInfo();
private:
    friend class odb::access;
    reserva();

#pragma db id auto
    unsigned int _id;

#pragma db column("data")
    std::string _data;

#pragma db column("num_places")
    int _num_places;

#pragma db column("preu_pagat")
    float _preu_pagat;

#pragma db not_null
    std::shared_ptr<usuari> _usuari;

#pragma db not_null
    std::shared_ptr<experiencia> _experiencia;
};

#endif