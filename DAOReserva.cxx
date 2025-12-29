#include "DAOReserva.hxx"
#include "connexioBD.hxx"

#include <odb/transaction.hxx>
#include <odb/query.hxx>

#include "reserva.hxx"
#include "reserva-odb.hxx"

DAOReserva::DAOReserva() {
    _db = connexioBD::getInstance().getDB();
}

bool DAOReserva::teAlgunaReserva(const std::string& sobrenom) {
    using odb::core::transaction;

    transaction t(_db->begin());

    typedef odb::query<reserva> query;
    typedef odb::result<reserva> result;

    // ODB: reservas cuyo usuario tiene ese sobrenom (ID de usuari)
    result r = _db->query<reserva>(query::usuari->sobrenom == sobrenom);

    bool existe = !r.empty();

    t.commit();
    return existe;
}
