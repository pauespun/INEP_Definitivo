#include "CtrlReservaEscapada.hxx"
#include "DAOEscapada.hxx"
#include "DAOReserva.hxx"
#include "PlanGo.hxx"
#include "reserva.hxx"
#include <stdexcept>
#include "Excepcions.hxx"      // ✅ Important
#include <odb/exceptions.hxx>

// Ya no necesitamos reserva-odb.hxx ni usuari-odb.hxx aquí, 
// porque el controlador ya no hace persist/update directo.
// Solo necesitamos acceso a BD para la transacción.

CtrlReservaEscapada::CtrlReservaEscapada() {}

DTOExperiencia CtrlReservaEscapada::consulta_escapada(const std::string& nom_escapada) {
    DAOEscapada dao;
    try {
        // Intentem recuperar l'escapada
        _escapada_actual = dao.obte(nom_escapada);
    }
    catch (const odb::object_not_persistent&) {
        // ✅ Si ODB diu que no existeix, llancem la nostra excepció de domini
        throw EscapadaNoExisteix();
    }
    catch (...) {
        // Per qualsevol altre error inesperat
        throw EscapadaNoExisteix();
    }

    // Retornem el DTO amb les dades
    return DTOExperiencia(
        _escapada_actual->get_nom(),
        _escapada_actual->get_descripcio(),
        _escapada_actual->get_ciutat(),
        _escapada_actual->get_maxim_places(),
        _escapada_actual->get_preu(),
        _escapada_actual->get_hotel(),
        _escapada_actual->get_num_nits(),
        0 // Durada és 0 per escapades
    );
}

DTOReserva CtrlReservaEscapada::reserva_escapada() {
    // 1. Validacions
    if (!_escapada_actual) throw std::runtime_error("Escapada no seleccionada.");

    auto u = PlanGo::getInstance().getUsuariLoggejat();
    if (!u) throw std::runtime_error("Usuari no loguejat.");

    // 2. Comprovar disponibilitat (Opcional, segons lògica d'escapades)
    DAOReserva daoRes;
    // ... lògica de places si cal ...

    // 3. Calcular preu (si té lògica de descomptes, aplica-la aquí)
    float preu = _escapada_actual->get_preu();

    // Si l'usuari no té reserves prèvies, apliquem descompte (Exemple)
    if (!daoRes.teAlgunaReserva(u->get_sobrenom())) {
        float descompte = PlanGo::getInstance().get_descompte();
        preu = preu * (1.0f - descompte);
    }

    // 4. Crear la reserva (Aquí es genera la Data/Hora automàticament al constructor)
    // Assumim que una escapada reserva totes les places o 1 plaça per defecte segons el teu domini.
    // Aquí poso '1' plaça com a exemple estàndard d'escapada, ajusta-ho si cal.
    int placesReservades = _escapada_actual->get_maxim_places(); // O 1, segons com ho tinguis

    auto r = std::make_shared<reserva>(u, _escapada_actual, placesReservades, preu);

    // 5. Guardar a la BD
    daoRes.inserta(*r);

    return r->obteInfo();
}