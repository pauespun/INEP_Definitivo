#include "DAOActivitat.hxx"
#include "activitat-odb.hxx"   // Archivo generado por ODB
#include <odb/transaction.hxx>
#include "connexioBD.hxx"

// Asumimos que la conexión a la BD está disponible externamente
extern std::shared_ptr<odb::mysql::database> db_conn;

DAOActivitat::DAOActivitat() {
    // Obtenim la connexió del teu Singleton
    _db = connexioBD::getInstance().getDB();
}

std::shared_ptr<activitat> DAOActivitat::obte(const std::string& nom) {
    using namespace odb::core;

    transaction t(_db->begin());

    // Consulta ODB: buscar activitat por nombre
    typedef odb::query<activitat> query;
    std::shared_ptr<activitat> result(_db->query_one<activitat>(query::nom == nom));

    t.commit();

    if (!result) {
        throw ActivitatNoExisteix();  // <-- asegúrate que existe en Excepcions.hxx
    }

    return result;
}

std::vector<std::shared_ptr<activitat>>
DAOActivitat::obtePerCiutatIPersones(const std::string& ciutat, int numPersones)
{
    using namespace odb::core;

    transaction t(_db->begin());

    typedef odb::query<activitat> query;
    typedef odb::result<activitat> result;

    query q = (query::ciutat == ciutat && query::maxim_places >= numPersones);

    result r = _db->query<activitat>(q + " ORDER BY " + query::maxim_places + " ASC");

    std::vector<std::shared_ptr<activitat>> llista;
    for (auto it = r.begin(); it != r.end(); ++it) {
        llista.push_back(it.load());
    }

    t.commit();
    return llista;
}