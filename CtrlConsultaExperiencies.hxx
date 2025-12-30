#pragma once

#include <string>
#include <vector>

#include "DTOExperiencia.hxx"

class CtrlConsultaExperiencies {
public:
    std::vector<DTOExperiencia>
        consulta_escapades(const std::string& ciutat, int numPersones);

    std::vector<DTOExperiencia>
        consulta_activitats(const std::string& ciutat, int numPersones);
};
