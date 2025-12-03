//CapaDePresentacio.hxx
#pragma once
#include <iostream>
#include <string>
#include "CapaDeDomini.hxx"
#include "DTOUsuari.hxx"
using namespace std;
using namespace boost::gregorian;
class CapaDePresentacio
{
public:
	// Patró Solter
	static CapaDePresentacio& getInstance() {
		static CapaDePresentacio instance;
		return instance;
	}
	// Operacions de presentació (només cin/cout)
	void crear_usuari();
	void llegir_usuaris();
	void llegir_usuari();
	void actualitzar_usuari();
	void esborrar_usuari();
private:
	//constructor de la classe
	CapaDePresentacio() = default;
};
