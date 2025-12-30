#include "activitat.hxx"
#include "PlanGo.hxx"
#include <stdexcept>


activitat::activitat() {}

activitat::activitat(const std::string& nom, const std::string& desc, const std::string& ciutat,
    int max_places, float preu, const std::string& data,
    int durada)
{
    _nom = nom;
    _descripcio = desc;
    _ciutat = ciutat;
    _maxim_places = max_places;
    _preu = preu;
    _data_alta = data;
    _num_reserves = 0;
    _durada = durada;
}

activitat::~activitat() {}

int activitat::get_durada() const {
    return _durada;
}

void activitat::set_durada(int d) {
    _durada = d;
}

float activitat::calculaPreu(int nPersones) const
{
    if (nPersones < 1)
        throw std::invalid_argument("Error: nPersones ha de ser >= 1.");

    return _preu * nPersones;
}
void activitat::ompleDetalls(DTOExperiencia& dto) const {
    dto.set_durada(get_durada());
}