#pragma once
#include <string>
#include "DAOUsuari.hxx"

// EXCEPCIONES SIMPLIFICADAS
struct SobrenomExisteix {};
struct CorreuExisteix {};
struct MenorEdat {};

class CtrlRegistraUsuari {
public:
    void registrarUsuari(const std::string& nom, const std::string& sobrenom,
        const std::string& contrasenya, const std::string& correu, int edat);
};