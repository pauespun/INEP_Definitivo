#pragma once
#include <string>
#include "DAOUsuari.hxx"
#include "Excepcions.hxx"

class CtrlIniciSessio {
public:
    // Método principal
    void iniciSessio(const std::string& sobrenom, const std::string& contrasenya);
};
