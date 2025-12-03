// DAOUsuari.hxx
#pragma once
#include <memory>
#include <vector>
#include <string>
#include <odb/core.hxx>
#include <odb/mysql/database.hxx>
#include "usuari-odb.hxx" // fitxer generat per ODB
#include "usuari.hxx"
#include "connexioBD.hxx"
class DAOUsuari {
public:
	DAOUsuari();
	// Operacions sobre usuari
	bool existeix(const std::string& username);
	usuari obte(const std::string& username);
	std::vector<usuari> tots();
	void inserta(const usuari& u);
	void modifica(const usuari& u);
	void esborra(const std::string& username);
private:
	std::shared_ptr<odb::mysql::database> db;
};
