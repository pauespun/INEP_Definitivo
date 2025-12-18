#pragma once
#include <string>
#include "DAOUsuari.hxx"

// EXCEPCIONES SIMPLIFICADAS (structs vacíos)
struct UsuariNoExisteix {};
struct ErrorContrasenya {};

class CtrlIniciSessio {
public:
    // Método principal
    void iniciSessio(const std::string& sobrenom, const std::string& contrasenya);
};
