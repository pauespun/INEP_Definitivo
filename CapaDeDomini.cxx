// CapaDeDomini.cxx
#include "CapaDeDomini.hxx"
#include "DAOUsuari.hxx"
#include <stdexcept>
using namespace std;
using namespace boost::gregorian;
void CapaDeDomini::registrarUsuari(const string& username, const string& nomcomplet, const date&
	data_naixement)
{
	DAOUsuari usuariDao;
	if (usuariDao.existeix(username))
		throw runtime_error("Ja existeix un usuari amb aquest username.");
	usuari u(username, nomcomplet, data_naixement);
	usuariDao.inserta(u);
}
void CapaDeDomini::esborrarUsuari(const string& username)
{
	DAOUsuari usuariDao;
	if (!usuariDao.existeix(username))
		throw runtime_error("No es pot esborrar: l'usuari no existeix.");
	usuariDao.esborra(username);
}
void CapaDeDomini::modificarUsuari(const string& username,
	const string& nou_nom,
	const date& nova_data)
{
	DAOUsuari usuariDao;
	if (!usuariDao.existeix(username))
		throw runtime_error("No es pot modificar: l'usuari no existeix.");
	usuari u = usuariDao.obte(username);
	u.set_nomcomplet(nou_nom);
	u.set_data_naixement(nova_data);
	usuariDao.modifica(u);
}//implementació del mètode amb DTOUsuari
DTOUsuari CapaDeDomini::consultarUsuari(const string& username)
{
	DAOUsuari usuariDao;
	usuari u = usuariDao.obte(username);
	return u;
}