#pragma once

#include <vector>
#include "DTOExperiencia.hxx"

class CtrlConsultaMesReservades {
public:
    std::vector<DTOExperiencia> consulta_escapades(int numElems = 5);
    std::vector<DTOExperiencia> consulta_activitats(int numElems = 5);
};
