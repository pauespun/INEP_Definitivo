#ifndef CTRLRESERVAACTIVITAT_HXX
#define CTRLRESERVAACTIVITAT_HXX

#include <string>
#include <memory>
#include "DTOExperiencia.hxx"
#include "activitat.hxx"

class CtrlReservaActivitat {
public:
    CtrlReservaActivitat();

    // Consulta la activitat y devuelve el DTO para mostrar en pantalla
    DTOExperiencia consulta_activitat(const std::string& nom_activitat);
    float preu_total(int numPersones) const;
    // Realiza la reserva usando la activitat guardada en memoria y el nº de personas
    float reserva_activitat(int numPersones);

private:
    // Guardamos la activitat consultada para usarla al reservar (Estado de sesión)
    std::shared_ptr<activitat> _activitat_actual;
};

#endif
