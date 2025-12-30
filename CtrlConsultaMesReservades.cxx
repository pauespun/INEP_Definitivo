#include "CtrlConsultaMesReservades.hxx"

#include <stdexcept>
#include <memory>

#include "DAOEscapada.hxx"
#include "DAOActivitat.hxx"
#include "escapada.hxx"
#include "activitat.hxx"

using namespace std;

static void validar_num_elems(int n) {
    if (n <= 0)
        throw invalid_argument("El nombre d'elements ha de ser major que 0.");
}

// =======================================================
// ESCAPADES MÉS RESERVADES
// =======================================================
vector<DTOExperiencia>
CtrlConsultaMesReservades::consulta_escapades(int numElems)
{
    validar_num_elems(numElems);

    DAOEscapada dao;
    vector<shared_ptr<escapada>> escapades =
        dao.obte_per_mes_reservades(numElems);

    vector<DTOExperiencia> resultat;
    resultat.reserve(escapades.size());

    for (const auto& e : escapades) {
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

    return resultat;
}

// =======================================================
// ACTIVITATS MÉS RESERVADES
// =======================================================
vector<DTOExperiencia>
CtrlConsultaMesReservades::consulta_activitats(int numElems)
{
    validar_num_elems(numElems);

    DAOActivitat dao;
    vector<shared_ptr<activitat>> activitats =
        dao.obte_per_mes_reservades(numElems);

    vector<DTOExperiencia> resultat;
    resultat.reserve(activitats.size());

    for (const auto& a : activitats) {
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

    return resultat;
}
