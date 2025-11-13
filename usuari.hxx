// usuari.hxx
#pragma once
#include <odb/core.hxx>
#include <string>
using namespace std;
// Anotació per definir que aquesta classe és un objecte perquè el reconeixi el compilador de ODB
#pragma db object
class usuari
{
public:
	usuari() = default;
	usuari(string username, string nomcomplet, int edat);
	string get_username();
	string get_nomcomplet();
	int get_edat();
	void set_username(string username);
	void set_nomcomplet(string nomcomplet);
	void set_edat(int edat);
private:
	// Permet a ODB accedir als membres privats de la classe per fer la persistència
	friend class odb::access;
#pragma db id // Anotació per indicar que l'atribut és clau primaria
	string _username;
	string _nomcomplet;
	int _edat;
};
