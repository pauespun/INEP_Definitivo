#ifndef CTRLRESERVAESCAPADA_HXX
#define CTRLRESERVAESCAPADA_HXX

#include <string>
#include <memory>
#include "DTOExperiencia.hxx"
#include "escapada.hxx"

class CtrlReservaEscapada {
public:
    CtrlReservaEscapada();

    // Consulta la escapada y devuelve el DTO para mostrar en pantalla
    DTOExperiencia consulta_escapada(const std::string& nom_escapada);

    // Realiza la reserva usando la escapada guardada en memoria
    float reserva_escapada();

private:
    // Guardamos la escapada consultada para usarla al reservar (Estado de sesión)
    std::shared_ptr<escapada> _escapada_actual;
};

#endif