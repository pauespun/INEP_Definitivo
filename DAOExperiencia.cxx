#include "DAOExperiencia.hxx"

#include "escapada.hxx"
#include "activitat.hxx"
#include "escapada-odb.hxx"
#include "activitat-odb.hxx"

#include <odb/transaction.hxx>
#include <odb/query.hxx>
#include <odb/result.hxx>

#include "connexioBD.hxx"

using namespace std;
using namespace odb::core;

DAOExperiencia::DAOExperiencia()
{
    _db = connexioBD::getInstance().getDB();
}

vector<DTOExperiencia>
DAOExperiencia::obte_novetats(int numElems)
{
    transaction t(_db->begin());

    vector<DTOExperiencia> resultat;

    // --- Escapades ---
    {
        typedef query<escapada> Q;
        typedef result<escapada> R;

        R r = _db->query<escapada>(
            "ORDER BY " + Q::data_alta + " DESC LIMIT " + to_string(numElems)
        );

        for (auto it = r.begin(); it != r.end(); ++it) {
            auto e = it.load();
            resultat.emplace_back(
                e->get_nom(),
                e->get_descripcio(),
                e->get_ciutat(),
                e->get_maxim_places(),
                e->get_preu(),
                e->get_hotel(),
                e->get_num_nits(),
                0
            );
        }
    }

    // --- Activitats ---
    {
        typedef query<activitat> Q;
        typedef result<activitat> R;

        R r = _db->query<activitat>(
            "ORDER BY " + Q::data_alta + " DESC LIMIT " + to_string(numElems)
        );

        for (auto it = r.begin(); it != r.end(); ++it) {
            auto a = it.load();
            resultat.emplace_back(
                a->get_nom(),
                a->get_descripcio(),
                a->get_ciutat(),
                a->get_maxim_places(),
                a->get_preu(),
                "",
                0,
                a->get_durada()
            );
        }
    }

    t.commit();
    return resultat;
}
