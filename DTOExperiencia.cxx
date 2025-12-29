#include "DTOExperiencia.hxx"

DTOExperiencia::DTOExperiencia() {}

DTOExperiencia::DTOExperiencia(std::string nom, std::string desc, std::string ciutat,
    int max_places, float preu, std::string hotel, int nits, int durada)
{
    _nom = nom;
    _descripcio = desc;
    _ciutat = ciutat;
    _maxim_places = max_places;
    _preu = preu;
    _hotel = hotel;
    _num_nits = nits;
    _durada = durada;
}

std::string DTOExperiencia::get_nom() const { return _nom; }
std::string DTOExperiencia::get_descripcio() const { return _descripcio; }
std::string DTOExperiencia::get_ciutat() const { return _ciutat; }
int DTOExperiencia::get_maxim_places() const { return _maxim_places; }
float DTOExperiencia::get_preu() const { return _preu; }
std::string DTOExperiencia::get_hotel() const { return _hotel; }
int DTOExperiencia::get_num_nits() const { return _num_nits; }
int DTOExperiencia::get_durada() const { return _durada; }