//connexioBD.cxx
#include "connexioBD.hxx"
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
shared_ptr<odb::mysql::database> connexioBD::getDB() const
{
	return _db;
}
// Funció aux. per carregar les variables d'entorn des d'un fitxer tipus .env
// Retorna un map amb les variables clau-valor
map<string, string> connexioBD::carregar_env(const string& fitxer)
{
	// Obrim el fitxer
	ifstream in(fitxer);
	// Comprovem que s'ha obert correctament
	if (!in.is_open())
		throw runtime_error("No s'ha pogut obrir el fitxer configuracio.env");
	// Llegim línia a línia
	map<string, string> vars;
	string linia;
	while (getline(in, linia))
	{
		// Ignorem línies buides o comentaris del fitxer configuracio.env
		if (linia.empty() || linia[0] == '#')
			continue;
		//Busquem el signe '=' per separar clau i valor
		auto pos = linia.find('=');
		// Si no el trobem, ignorem la línia
		if (pos == string::npos)
			continue;
		//Separem clau i valor i les afegim al map
		string clau = linia.substr(0, pos); // abans del '='
		string valor = linia.substr(pos + 1); // després del '='
		vars[clau] = valor; // Afegim al map
	}
	// Tanquem el fitxer i retornem el map
	return vars;
}
// Implementació del patró singleton per la classe connexio
connexioBD& connexioBD::getInstance()
{
	static connexio instance;
	return instance;
}// Constructor privat que llegeix les variables d'entorn i crea la connexió a la base de dades
connexioBD::connexioBD()
{
	// Carreguem les variables d'entorn des del fitxer configuracio.env
	auto env = carregar_env("configuracio.env");
	// Obtenim les variables necessàries per establir la connexió
	string user = env["DB_USER"];
	string pass = env["DB_PASS"];
	string name = env["DB_NAME"];
	string host = env["DB_HOST"];
	// Comprovem que totes les variables estan presents
	if (user.empty() || pass.empty() || name.empty() || host.empty())
		throw runtime_error("Falten variables de configuració a .env");
	// Creem la connexió a la base de dades MySQL
	_db = make_shared<odb::mysql::database>(user, pass, name, host);
}