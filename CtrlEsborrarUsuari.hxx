#pragma once
#include <string>
#include "Excepcions.hxx"

class CtrlEsborrarUsuari {
public:
    // Ahora recibe la contraseña para verificarla antes de borrar
    void esborrarUsuari(const std::string& contrasenya);
};