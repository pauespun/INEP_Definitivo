//connexioBD.hxx
#pragma once
#include <memory>
#include <string>
#include <odb/mysql/database.hxx>
using namespace std;
class connexioBD
{
public:
	// Singleton
	static connexioBD& getInstance();
	shared_ptr<odb::mysql::database> getDB() const;
	//retorna la connexió a la base de dades
	//es de tipus const perque no modifica l'objecte singleton
private:
	connexioBD(); // llegirà el .env i crearà la connexió
	map<string, string> carregar_env(const string& fitxer);
	shared_ptr<odb::mysql::database> _db;
};