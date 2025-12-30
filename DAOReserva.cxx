#include "DAOReserva.hxx"
#include "connexioBD.hxx"

#include <odb/transaction.hxx>
#include <odb/query.hxx>

// ✅ Includes necessaris perquè el compilador entengui la classe 'reserva' i les queries
#include "reserva.hxx"
#include "reserva-odb.hxx" 

DAOReserva::DAOReserva() {
    _db = connexioBD::getInstance().getDB();
}

bool DAOReserva::teAlgunaReserva(const std::string& sobrenom) {
    using odb::core::transaction;

    typedef odb::query<reserva> query;
    typedef odb::result<reserva> result;

    if (transaction::has_current()) {
        result r = _db->query<reserva>(query::usuari->sobrenom == sobrenom);
        return !r.empty();
    }
    else {
        transaction t(_db->begin());
        result r = _db->query<reserva>(query::usuari->sobrenom == sobrenom);
        bool existe = !r.empty();
        t.commit();
        return existe;
    }
}

// ✅ Mètode recuperat exactament com el tenies
int DAOReserva::placesOcupades(const std::string& nomExperiencia) {
    using odb::core::transaction;

    typedef odb::query<reserva> query;
    typedef odb::result<reserva> result;

    // Lògica de la consulta (lambda)
    auto fer_consulta = [&](odb::database& db) {
        // Nota: Assegura't que 'experiencia' és el nom del punter a reserva.hxx
        result r = db.query<reserva>(query::experiencia->nom == nomExperiencia);
        int total = 0;
        for (const auto& res : r) {
            total += res.get_num_places();
        }
        return total;
        };

    if (transaction::has_current()) {
        return fer_consulta(*_db);
    }
    else {
        transaction t(_db->begin());
        int total = fer_consulta(*_db);
        t.commit();
        return total;
    }
}

void DAOReserva::inserta(reserva& r) {
    using odb::core::transaction;

    if (transaction::has_current()) {
        _db->persist(r);
    }
    else {
        transaction t(_db->begin());
        _db->persist(r);
        t.commit();
    }
}
