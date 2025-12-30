#include "DTOReserves.hxx"

DTOReserves::DTOReserves() : _totalPagat(0.0f) {}

void DTOReserves::afegirReserva(const DTOReserva& reserva) {
    // 1. L'afegim a la llista
    _llista.push_back(reserva);

    // 2. Sumem el seu preu al total acumulat (Lògica de contenidor)
    _totalPagat += reserva.get_preuPagat();
}

float DTOReserves::get_totalPagat() const { return _totalPagat; }

std::vector<DTOReserva> DTOReserves::get_llista() const { return _llista; }