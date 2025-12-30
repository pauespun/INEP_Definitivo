#include "DAOUsuari.hxx"
#include "connexioBD.hxx" 
#include "usuari-odb.hxx" 
#include <odb/transaction.hxx>

using namespace std;

DAOUsuari::DAOUsuari() {
    db = connexioBD::getInstance().getDB();
}

bool DAOUsuari::existeix(const string& sobrenom) {
    odb::transaction t(db->begin());

    auto result = db->query<usuari>(odb::query<usuari>::sobrenom == sobrenom);
    bool existe = !result.empty();

    t.commit();
    return existe;
}

bool DAOUsuari::existeixEmail(const string& email) {
    odb::transaction t(db->begin());

    auto result = db->query<usuari>(odb::query<usuari>::correuElectronic == email);
    bool existe = !result.empty();

    t.commit();
    return existe;
}

std::vector<usuari> DAOUsuari::tots() {
    odb::transaction t(db->begin());

    odb::result<usuari> r = db->query<usuari>();

    std::vector<usuari> llista;
    for (auto& u : r) {
        llista.push_back(u);
    }

    t.commit();
    return llista;
}

usuari DAOUsuari::obte(const string& sobrenom) {
    odb::transaction t(db->begin());
    // Load carga por clave primaria
    auto u_ptr = db->load<usuari>(sobrenom);
    usuari u = *u_ptr;
    t.commit();
    return u;
}

void DAOUsuari::inserta(const usuari& u) {
    odb::transaction t(db->begin());
    db->persist(u);
    t.commit();
}

void DAOUsuari::modifica(const usuari& u) {
    odb::transaction t(db->begin());
    db->update(u);
    t.commit();
}

void DAOUsuari::esborra(const string& sobrenom) {
    odb::transaction t(db->begin());
    db->erase<usuari>(sobrenom);
    t.commit();
}