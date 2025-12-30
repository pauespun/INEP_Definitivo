#include "CtrlRegistraUsuari.hxx"
#include "DAOUsuari.hxx"
#include "Excepcions.hxx" 
// #include <odb/exceptions.hxx> // Ja no cal tant

void CtrlRegistraUsuari::registrarUsuari(const std::string& nom, const std::string& sobrenom,
    const std::string& contrasenya, const std::string& correu, int edat) {

    // 1. Validar edat
    if (edat < 18) {
        throw MenorEdat();
    }

    DAOUsuari dao;

    // 2. Comprovar si el SOBRENOM ja existeix (Manualment)
    // El teu DAO ja té un mètode 'existeix' (o usa obte + try-catch)
    if (dao.existeix(sobrenom)) {
        throw SobrenomExisteix();
    }

    // 3. Comprovar si el CORREU ja existeix (Manualment)
    // Utilitza el mètode 'existeixEmail' que tens al codi que m'has passat
    if (dao.existeixEmail(correu)) {
        throw CorreuExisteix();
    }

    // 4. Si passem les validacions, creem i inserim
    usuari nouUsuari(sobrenom, nom, correu, contrasenya, edat);

    // Ara la inserció no hauria de fallar per duplicats (llevat de condicions de carrera molt rares)
    dao.inserta(nouUsuari);
}