#include "CtrlConsultaNovetats.hxx"

#include <stdexcept>

#include "DAOExperiencia.hxx"

using namespace std;

vector<DTOExperiencia>
CtrlConsultaNovetats::consultar_novetats(int numElems)
{
    if (numElems <= 0)
        throw invalid_argument("El nombre d'elements ha de ser major que 0.");

    DAOExperiencia dao;
    return dao.obte_novetats(numElems);
}
