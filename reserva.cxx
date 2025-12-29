#define _CRT_SECURE_NO_WARNINGS
#include "reserva.hxx"
#include "usuari.hxx"
#include "experiencia.hxx"
#include <ctime> 

// Función auxiliar local
std::string obtener_fecha_actual_reserva() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return std::string(buf);
}

reserva::reserva() {
}

reserva::reserva(std::shared_ptr<usuari> u, std::shared_ptr<experiencia> e, int places, float pagat) {
    _usuari = u;
    _experiencia = e;
    _num_places = places;
    _preu_pagat = pagat;
    _data = obtener_fecha_actual_reserva();
}

reserva::~reserva() {
}

unsigned int reserva::get_id() const {
    return _id;
}

std::string reserva::get_data() const {
    return _data;
}

int reserva::get_num_places() const {
    return _num_places;
}

float reserva::get_preu_pagat() const {
    return _preu_pagat;
}

std::shared_ptr<usuari> reserva::get_usuari() const {
    return _usuari;
}

std::shared_ptr<experiencia> reserva::get_experiencia() const {
    return _experiencia;
}

void reserva::set_data(const std::string& d) {
    _data = d;
}