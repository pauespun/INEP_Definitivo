#ifndef DTORESERVA_HXX
#define DTORESERVA_HXX

#include <string>
#include "DTOExperiencia.hxx"

class DTOReserva {
public:
    // Constructor buit
    DTOReserva();

    // Constructor complet
    DTOReserva(std::string data, int numPlaces, float preuPagat, DTOExperiencia experiencia);

    // Getters
    std::string get_data() const;
    int get_numPlaces() const;
    float get_preuPagat() const;
    DTOExperiencia get_experiencia() const;

private:
    std::string _data;
    int _numPlaces;
    float _preuPagat;
    DTOExperiencia _experiencia;
};

#endif