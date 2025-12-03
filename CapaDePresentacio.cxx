//CapaDePresentacio.cxx
#include "CapaDePresentacio.hxx"
#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
void CapaDePresentacio::crear_usuari()
{
	string user, nom;
	int any, mes, dia;
	cout << "Introdueix username: ";
	cin >> user;
	cout << "Introdueix nom complet: ";
	cin.ignore();
	getline(cin, nom);
	cout << "Introdueix data de naixement (DD MM AAAA): ";
	cin >> dia >> mes >> any;
	date data_naixement(any, mes, dia);
	CapaDeDomini& domini = CapaDeDomini::getInstance();
	try {
		domini.registrarUsuari(user, nom, data_naixement);
		cout << "Usuari creat.\n";
	}
	catch (const exception& e) {
		cout << "Error al crear l'usuari: " << e.what() << endl;
	}
}

void CapaDePresentacio::esborrar_usuari()
{
	string user;
	cout << "Username de l'usuari a esborrar: ";
	cin >> user;
	CapaDeDomini& domini = CapaDeDomini::getInstance();
	try {
		domini.esborrarUsuari(user);
		cout << "Usuari esborrat.\n";
	}
	catch (const exception& e) {
		cout << "Error al esborrar l'usuari: " << e.what() << endl;
	}
}
//Exemple funcio per actualitzar un usuari opcionalment camp a camp
void CapaDePresentacio::actualitzar_usuari() {
	string user;
	cout << "Username de l'usuari a modificar: ";
	cin >> user;
	CapaDeDomini& domini = CapaDeDomini::getInstance();
	try {
		//Recuperem les dades actuals de l’usuari des de la capa de domini
		DTOUsuari dto = domini.consultarUsuari(user);
		cout << "Dades actuals:\n";
		cout << "Nom: " << dto.get_nomcomplet() << endl;
		cout << "Data naixement: " << dto.get_data_naixement() << endl;
		// Eliminem el salt de línia pendent després de llegir amb '>>'
		// max() indica que es descarti tot el que quedi al buffer fins trobar un '\n'
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string nou_nom;
		cout << "\nNou nom complet (enter per mantenir): ";
		getline(cin, nou_nom);
		if (nou_nom.empty()) {
			// Si no s’escriu res, mantenim el nom actual
			nou_nom = dto.get_nomcomplet();
		}
		cout << "Nova data de naixement (DD MM AAAA) (enter per mantenir): ";
		string linia_data;
		getline(cin, linia_data);
		// Per defecte, conservem la data existent
		date nova_data = dto.get_data_naixement();
		if (!linia_data.empty()) {
			int dia, mes, any;
			std::istringstream iss(linia_data);
			if (iss >> dia >> mes >> any) {
				nova_data = date(any, mes, dia);
			}
		}
		domini.modificarUsuari(user, nou_nom, nova_data);
	}
	catch (const exception& e) {
		cout << "Error al actualitzar l'usuari: " << e.what() << endl;
	}
}

void CapaDePresentacio::llegir_usuari()
{
	string user;
	cout << "Username de l'usuari a consultar: ";
	cin >> user;
	CapaDeDomini& domini = CapaDeDomini::getInstance();
	// Ara la capa de domini retorna un DTOUsuari
	DTOUsuari dto = domini.consultarUsuari(user);
	cout << "Username: " << dto.get_username() << endl;
	cout << "Nom: " << dto.get_nomcomplet() << endl;
	cout << "Data naixement: " << dto.get_data_naixement() << endl;
}

