#ifndef DAOESCAPADA_HXX
#define DAOESCAPADA_HXX

#include <string>
#include <memory>
#include <odb/mysql/database.hxx>
#include "escapada.hxx"

#include "Excepcions.hxx"

class DAOEscapada {
public:
    DAOEscapada();

    // Método para obtener la entidad escapada
    std::shared_ptr<escapada> obte(const std::string& nom);

    // Para "Consultar experiències"
    std::vector<std::shared_ptr<escapada>>
    obtePerCiutatIPersones(const std::string& ciutat, int numPersones);

	// Para "Consultar escapades més reservades"
    std::vector<std::shared_ptr<escapada>>
    obte_per_mes_reservades(int numElems);

private:
    // Puntero a la base de datos (se inicializará con la conexión global)
    std::shared_ptr<odb::mysql::database> _db;
};

#endif