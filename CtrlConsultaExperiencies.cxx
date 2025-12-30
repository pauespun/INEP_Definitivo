#include "CtrlConsultaExperiencies.hxx"

#include <stdexcept>
#include <memory>

#include "DAOEscapada.hxx"
#include "DAOActivitat.hxx"
#include "escapada.hxx"
#include "activitat.hxx"

using namespace std;

static void validar_num_persones(int numPersones)
{
    if (numPersones <= 0)
        throw invalid_argument("El nombre de persones ha de ser major que 0.");
}

// =======================================================
// CONSULTAR ESCAPADES
// =======================================================
vector<DTOExperiencia>
CtrlConsultaExperiencies::consulta_escapades(
    const string& ciutat,
    int numPersones)
{
    validar_num_persones(numPersones);

    DAOEscapada dao;
    vector<shared_ptr<escapada>> escapades =
        dao.obtePerCiutatIPersones(ciutat, numPersones);

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
            0               // durada = 0 en escapades
        );
    }

    return resultat;
}

// =======================================================
// CONSULTAR ACTIVITATS
// =======================================================
vector<DTOExperiencia>
CtrlConsultaExperiencies::consulta_activitats(
    const string& ciutat,
    int numPersones)
{
    validar_num_persones(numPersones);

    DAOActivitat dao;
    vector<shared_ptr<activitat>> activitats =
        dao.obtePerCiutatIPersones(ciutat, numPersones);

    vector<DTOExperiencia> resultat;
    resultat.reserve(activitats.size());

    for (const auto& a : activitats) {
        resultat.emplace_back(
            a->get_nom(),
            a->get_descripcio(),
            a->get_ciutat(),
            a->get_maxim_places(),
            a->get_preu(),
            "",             // hotel vacío en activitats
            0,              // num_nits = 0
            a->get_durada()
        );
    }

    return resultat;
}
