// usuari.hxx
#pragma once
#include <odb/core.hxx>
#include <string>
#include "model.hxx"
#include "DTOUsuari.hxx"
#include <vector>
#include <memory>
#include "experiencia.hxx"
class reserva;


#pragma db object
class usuari : public std::enable_shared_from_this<usuari>
{
public:
    usuari() = default;
    usuari(std::string sobrenom, std::string nom, std::string correu, std::string contra, int edat);

    // Getters
    std::string get_sobrenom() const;
    std::string get_nom() const;
    std::string get_correuElectronic() const;
    std::string get_contrasenya() const;
    int get_edat() const;

    // Setters
    void set_nom(std::string nom);
    void set_correuElectronic(std::string correu);
    void set_edat(int edat);


    bool comprovaContrasenya(const std::string& contra) const;

    float afegirReserva(std::shared_ptr<experiencia> e);
    float afegirReserva(std::shared_ptr<experiencia> e, int numPersones);

    float calculaPreuReserva(std::shared_ptr<experiencia> e, int numPersones) const;


    std::vector<std::shared_ptr<reserva>>& get_reserves();
    void set_reserves(const std::vector<std::shared_ptr<reserva>>& r);

    DTOUsuari obteInfo() const;

private:
    friend class odb::access;
#pragma db id
    std::string _sobrenom;
    std::string _nom;
#pragma db type("VARCHAR(255)") unique
    std::string _correuElectronic;
    std::string _contrasenya;
#pragma db options("CHECK(edat >= 18)")
    int _edat;
  
#pragma db value_not_null inverse(_usuari)
std::vector<std::shared_ptr<reserva>> _reserves;
};