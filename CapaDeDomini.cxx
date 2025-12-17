// CapaDeDomini.cxx
#include "CapaDeDomini.hxx"
#include "DAOUsuari.hxx"
#include "usuari.hxx"
#include <stdexcept>
#include <iostream>

using namespace std;

// Implementació del Singleton
CapaDeDomini& CapaDeDomini::getInstance()
{
    static CapaDeDomini instance;
    return instance;
}

void CapaDeDomini::registrarUsuari(const string& sobrenom, const string& nom,
    const string& correu, const string& contra, int edat)
{
    DAOUsuari usuariDao;

    // 1. Validar que l'usuari no existeix (PK)
    if (usuariDao.existeix(sobrenom)) {
        throw runtime_error("Error: Ja existeix un usuari amb aquest sobrenom.");
    }

    // 2. Validar que el correu no estigui repetit (RIT2)
    // Nota: Assegura't d'haver afegit 'existeixEmail' al teu DAOUsuari com vam parlar abans
    if (usuariDao.existeixEmail(correu)) {
        throw runtime_error("Error: Aquest correu electronic ja esta registrat.");
    }

    // 3. Validar majoria d'edat (RIT1)
    if (edat < 18) {
        throw runtime_error("Error: L'usuari ha de ser major d'edat (>= 18).");
    }

    // Si tot és correcte, creem l'objecte i el persistim
    usuari u(sobrenom, nom, correu, contra, edat);
    usuariDao.inserta(u);
}

DTOUsuari CapaDeDomini::consultarUsuari(const string& sobrenom)
{
    DAOUsuari usuariDao;
    if (!usuariDao.existeix(sobrenom)) {
        throw runtime_error("Error: L'usuari no existeix.");
    }

    // Recuperem l'objecte de domini
    usuari u = usuariDao.obte(sobrenom);

    // El convertim a DTO per enviar-lo a la presentació
    return DTOUsuari(u);
}

void CapaDeDomini::modificarUsuari(const string& sobrenom, const string& nou_nom,
    const string& nou_correu, int nova_edat)
{
    DAOUsuari usuariDao;
    if (!usuariDao.existeix(sobrenom)) {
        throw runtime_error("Error: No es pot modificar, l'usuari no existeix.");
    }

    // Recuperem l'usuari original
    usuari u = usuariDao.obte(sobrenom);

    // Apliquem canvis només si s'han proporcionat (no buits o diferents de -1)
    if (!nou_nom.empty()) {
        u.set_nom(nou_nom);
    }

    if (!nou_correu.empty()) {
        // Si canvia el correu, verifiquem que el nou no existeixi ja
        if (nou_correu != u.get_correuElectronic() && usuariDao.existeixEmail(nou_correu)) {
            throw runtime_error("Error: El nou correu electronic ja esta en us.");
        }
        u.set_correuElectronic(nou_correu);
    }

    if (nova_edat != -1) {
        if (nova_edat < 18) throw runtime_error("Error: L'usuari no pot ser menor d'edat.");
        u.set_edat(nova_edat);
    }

    // Guardem els canvis
    usuariDao.modifica(u);
}

void CapaDeDomini::esborrarUsuari(const string& sobrenom)
{
    DAOUsuari usuariDao;
    if (!usuariDao.existeix(sobrenom)) {
        throw runtime_error("Error: No es pot esborrar, l'usuari no existeix.");
    }
    usuariDao.esborra(sobrenom);
}