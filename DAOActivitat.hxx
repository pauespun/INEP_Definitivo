#ifndef DAOACTIVITAT_HXX
#define DAOACTIVITAT_HXX

#include <string>
#include <memory>
#include <odb/mysql/database.hxx>
#include "activitat.hxx"

#include "Excepcions.hxx"

class DAOActivitat {
public:
    DAOActivitat();

    // Método para obtener la entidad activitat
    std::shared_ptr<activitat> obte(const std::string& nom);

    // Para "Consultar experiències"
    std::vector<std::shared_ptr<activitat>>
    obtePerCiutatIPersones(const std::string& ciutat, int numPersones);

    std::vector<std::shared_ptr<activitat>>
    obte_per_mes_reservades(int numElems);

private:
    // Puntero a la base de datos (se inicializará con la conexión global)
    std::shared_ptr<odb::mysql::database> _db;
};

#endif
