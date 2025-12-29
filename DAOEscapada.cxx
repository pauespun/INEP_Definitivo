#include "DAOEscapada.hxx"
#include "escapada-odb.hxx" // Archivo generado por ODB
#include <odb/transaction.hxx>
#include "connexioBD.hxx"

// Asumimos que la conexión a la BD está disponible externamente
extern std::shared_ptr<odb::mysql::database> db_conn;

DAOEscapada::DAOEscapada() {
    // Obtenim la connexió del teu Singleton
    _db = connexioBD::getInstance().getDB();
}
std::shared_ptr<escapada> DAOEscapada::obte(const std::string& nom) {
    using namespace odb::core;

    transaction t(_db->begin());

    // Consulta ODB: buscar escapada por nombre
    typedef odb::query<escapada> query;
    std::shared_ptr<escapada> result(_db->query_one<escapada>(query::nom == nom));

    t.commit();

    if (!result) {
        throw EscapadaNoExisteix();
    }

    return result;
}