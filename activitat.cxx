#include "activitat.hxx"
#include "PlanGo.hxx"


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

float activitat::calculaPreu(int nPersones, bool primeraRes) {
    // Lógica: En actividad el precio es por persona
    float preu_final = this->get_preu() * nPersones;

    if (primeraRes) {
        float descompte = PlanGo::getInstance().get_descompte();
        preu_final = preu_final * (1.0f - descompte);
    }
    return preu_final;
}