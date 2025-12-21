#pragma once
#include <string>
#include "DTOUsuari.hxx"

class CtrlModificaUsuari {
public:
    // 1. Operación para mostrar los datos actuales (Reusa CtrlConsultaUsuari)
    DTOUsuari consultaUsuari();

    // 2. Operación para modificar y devolver los datos CONFIRMADOS de la BD
    DTOUsuari modificaUsuari(const std::string& nom, const std::string& correu, int edat);
};