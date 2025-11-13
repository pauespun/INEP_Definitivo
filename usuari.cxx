// usuari.cxx
#include "usuari.hxx"
usuari::usuari(string username, string nomcomplet, int edat) {
	_username = username;
	_nomcomplet = nomcomplet;
	_edat = edat;
}
string usuari::get_username() { return _username; }
string usuari::get_nomcomplet() { return _nomcomplet; }
int usuari::get_edat() { return _edat; }
void usuari::set_username(string username) { _username = username; }
void usuari::set_nomcomplet(string nomcomplet) { _nomcomplet = nomcomplet; }
void usuari::set_edat(int edat) { _edat = edat; }
