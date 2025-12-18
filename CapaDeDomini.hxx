// CapaDeDomini.hxx
#pragma once
#include <string>
#include <memory>
#include "DTOUsuari.hxx"

// Clase Façade que redirige a los controladores específicos
class CapaDeDomini
{
public:
    // Singleton
    static CapaDeDomini& getInstance();

  
    void registrarUsuari(const DTOUsuari& usuariDTO);

    void iniciarSessio(const std::string& sobrenom, const std::string& contrasenya);

    void tancaSessio();

private:
    CapaDeDomini() = default;
    CapaDeDomini(const CapaDeDomini&) = delete;
    CapaDeDomini& operator=(const CapaDeDomini&) = delete;
};