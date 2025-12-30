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

int DAOReserva::placesOcupades(const std::string& nomExperiencia) {
    using odb::core::transaction;

    typedef odb::query<reserva> query;
    typedef odb::result<reserva> result;

    // Lògica de la consulta
    auto fer_consulta = [&](odb::database& db) {
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

std::vector<std::shared_ptr<reserva>> DAOReserva::obteReservesUsuari(const std::string& sobrenom) {
    using odb::core::transaction;

    std::vector<std::shared_ptr<reserva>> resultat;

    typedef odb::query<reserva> query;
    typedef odb::result<reserva> result;

    transaction t(_db->begin());

    result r = _db->query<reserva>(
        (query::usuari->sobrenom == sobrenom) +
        " ORDER BY " + query::data + " DESC"
    );

    for (auto& res : r) {
        resultat.push_back(std::make_shared<reserva>(res));
    }

    t.commit();
    return resultat;
}