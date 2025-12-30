#include "DTOReserva.hxx"

DTOReserva::DTOReserva()
    : _data(""), _numPlaces(0), _preuPagat(0.0f) {
}

DTOReserva::DTOReserva(std::string data, int numPlaces, float preuPagat, DTOExperiencia experiencia)
    : _data(data), _numPlaces(numPlaces), _preuPagat(preuPagat), _experiencia(experiencia) {
}

std::string DTOReserva::get_data() const { return _data; }

int DTOReserva::get_numPlaces() const { return _numPlaces; }

float DTOReserva::get_preuPagat() const { return _preuPagat; }

DTOExperiencia DTOReserva::get_experiencia() const { return _experiencia; }