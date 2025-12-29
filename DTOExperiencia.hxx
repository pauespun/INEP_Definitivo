#ifndef DTOEXPERIENCIA_HXX
#define DTOEXPERIENCIA_HXX

#include <string>

class DTOExperiencia {
public:
    DTOExperiencia();
    // Constructor completo
    DTOExperiencia(std::string nom, std::string desc, std::string ciutat,
        int max_places, float preu, std::string hotel, int nits, int durada);

    // Getters
    std::string get_nom() const;
    std::string get_descripcio() const;
    std::string get_ciutat() const;
    int get_maxim_places() const;
    float get_preu() const;
    std::string get_hotel() const;
    int get_num_nits() const;
    int get_durada() const;

private:
    std::string _nom;
    std::string _descripcio;
    std::string _ciutat;
    int _maxim_places;
    float _preu;
    std::string _hotel;
    int _num_nits;
    int _durada;
};

#endif