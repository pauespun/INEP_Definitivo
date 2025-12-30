#pragma once

#include <vector>

#include "DTOExperiencia.hxx"

class CtrlConsultaNovetats {
public:
    std::vector<DTOExperiencia> consultar_novetats(int numElems = 10);
};
