#pragma once
#include <vector>
#include <memory>
#include <string>
#include <odb/database.hxx>
#include "usuari.hxx" // Tu clase del modelo
#include "DTOUsuari.hxx" // Si necesitas devolver DTOs, si no, quítalo

class DAOUsuari {
private:
    std::shared_ptr<odb::database> db; // Variable de la base de datos

public:
    DAOUsuari();

    // Métodos
    std::vector<usuari> tots();
    bool existeix(const std::string& sobrenom);
    bool existeixEmail(const std::string& email);
    usuari obte(const std::string& sobrenom);
    void inserta(const usuari& u);
    void modifica(const usuari& u);
    void esborra(const std::string& sobrenom);
};