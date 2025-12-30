#include "CtrlReservaActivitat.hxx"
#include "DAOActivitat.hxx"
#include "DAOReserva.hxx" 
#include "PlanGo.hxx"
#include "Excepcions.hxx"
#include <stdexcept>
#include "reserva.hxx"

CtrlReservaActivitat::CtrlReservaActivitat() {}

DTOExperiencia CtrlReservaActivitat::consulta_activitat(const std::string& nom_activitat) {
    DAOActivitat dao;
    try {
        // El DAO gestiona la connexió internament
        _activitat_actual = dao.obte(nom_activitat);
    }
    catch (...) {
        // Si el DAO falla (ex: object_not_persistent), llancem la nostra excepció de domini
        throw ActivitatNoExisteix();
    }

    return DTOExperiencia(
        _activitat_actual->get_nom(),
        _activitat_actual->get_descripcio(),
        _activitat_actual->get_ciutat(),
        _activitat_actual->get_maxim_places(),
        _activitat_actual->get_preu(),
        "", 0,
        _activitat_actual->get_durada()
    );
}

float CtrlReservaActivitat::preu_total(int numPersones) const {
    if (!_activitat_actual) throw std::runtime_error("Activitat no seleccionada.");
    if (numPersones < 1) throw std::invalid_argument("Mínim 1 persona.");

    // Validació de negoci (Escenari Alternatiu)
    if (numPersones > _activitat_actual->get_maxim_places()) {
        throw SuperaMaxim();
    }

    auto u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("Usuari no loguejat.");

    // Deleguem la consulta de BD al DAO
    DAOReserva daoReserva;

    // 1. Validar AFORO REAL 
    int ocupadas = daoReserva.placesOcupades(_activitat_actual->get_nom());
    if (ocupadas + numPersones > _activitat_actual->get_maxim_places()) {
        throw SuperaMaxim(); 
    }

    bool teReserves = daoReserva.teAlgunaReserva(u->get_sobrenom());

    float preu = _activitat_actual->get_preu() * numPersones;

    // Aplicar descompte (Lògica de negoci pura)
    if (!teReserves) {
        float descompte = PlanGo::getInstance().get_descompte();
        preu = preu * (1.0f - descompte);
    }

    return preu;
}

float CtrlReservaActivitat::reserva_activitat(int numPersones) {
    // 1. Validacions
    if (!_activitat_actual) throw std::runtime_error("Activitat no seleccionada.");
    if (numPersones > _activitat_actual->get_maxim_places()) throw SuperaMaxim();

    auto u = PlanGo::getInstance().getUsuariLoggejat();

    // 2. Càlcul del preu final (reutilitzem la lògica neta)
    float preuFinal = preu_total(numPersones);

    // 3. Creació de l'objecte de Domini (en memòria)
    // Utilitzem make_shared per crear l'objecte que espera ODB, però sense tocar DB encara
    auto r = std::make_shared<reserva>(u, _activitat_actual, numPersones, preuFinal);

    // 4. Persistència via DAO
    DAOReserva daoReserva;
    daoReserva.inserta(*r); // AQUI és on s'obre la connexió i la transacció, dins del DAO.

    return preuFinal;
}

int CtrlReservaActivitat::places_disponibles() {
    if (!_activitat_actual) return 0;

    DAOReserva dao;
    // 1. Preguntem quantes places estan ocupades realment
    int ocupades = dao.placesOcupades(_activitat_actual->get_nom());

    // 2. Calculem la diferència
    int lliures = _activitat_actual->get_maxim_places() - ocupades;

    // 3. Per seguretat, que no retorni negatius
    return (lliures < 0) ? 0 : lliures;
}

