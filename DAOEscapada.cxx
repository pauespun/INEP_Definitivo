#include "DAOEscapada.hxx"
#include "escapada-odb.hxx" 
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

std::vector<std::shared_ptr<escapada>>
DAOEscapada::obtePerCiutatIPersones(const std::string& ciutat, int numPersones)
{
    using namespace odb::core;

    transaction t(_db->begin());

    typedef odb::query<escapada> query;
    typedef odb::result<escapada> result;

    // Filtro por ciutat y capacidad
    query q = (query::ciutat == ciutat && query::maxim_places >= numPersones);

    // Orden ascendente por maxim_places
    // En ODB se puede concatenar SQL para ORDER BY:
    result r = _db->query<escapada>(q + " ORDER BY " + query::maxim_places + " ASC");

    std::vector<std::shared_ptr<escapada>> llista;
    for (auto it = r.begin(); it != r.end(); ++it) {
        llista.push_back(it.load());  
    }

    t.commit();
    return llista;
}

std::vector<std::shared_ptr<escapada>>
DAOEscapada::obte_per_mes_reservades(int numElems)
{
    using namespace odb::core;

    transaction t(_db->begin());

    typedef query<escapada> query;
    typedef result<escapada> result;

    result r = _db->query<escapada>(
        "ORDER BY " + query::num_reserves + " DESC, "
        + query::data_alta + " DESC LIMIT " + std::to_string(numElems)
    );

    std::vector<std::shared_ptr<escapada>> llista;
    for (auto it = r.begin(); it != r.end(); ++it) {
        llista.push_back(it.load());
    }

    t.commit();
    return llista;
}
