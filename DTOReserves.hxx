#ifndef DTORESERVES_HXX
#define DTORESERVES_HXX

#include <vector>
#include "DTOReserva.hxx"

class DTOReserves {
public:
    DTOReserves();

    // Mètode clau: Afegeix la reserva i suma el seu preu al total
    void afegirReserva(const DTOReserva& reserva);

    float get_totalPagat() const;
    std::vector<DTOReserva> get_llista() const;

private:
    float _totalPagat;
    std::vector<DTOReserva> _llista;
};

#endif