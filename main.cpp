#include <iostream>
#include <memory>
#include <string>
#include <odb/mysql/database.hxx>
#include <odb/transaction.hxx>
#include "usuari.hxx"
#include "usuari-odb.hxx"
using namespace std;
/*************************************************************************************/
// Gestió usuaris
/*************************************************************************************/
void crear_usuari(shared_ptr<odb::database> db) {
	string user, nom;
	int edat;
	cout << "Introdueix username: ";
	cin >> user;
	cout << "Introdueix nom complet: ";
	cin.ignore();
	getline(cin, nom);
	cout << "Introdueix edat: ";
	cin >> edat;
	// Per executar qualsevol comanda al MySQL es fa servir el concepte de transacció.
	// Una transacció comença al crear el odb::transaction i els canvis no es fan a la
	// base de dades fins que no executem la operació commit()
	try {
		odb::transaction t(db->begin());
		shared_ptr<usuari> u(new usuari(user, nom, edat));
		// La operació persist es fa servir per crear (CREATE en SQL)
		db->persist(u);
		t.commit();
		cout << "Usuari creat.\n";
	}
	catch (const odb::exception& e) {
		cout << "Error al crear l'usuari: " << e.what() << endl;
	}
}
void llegir_usuaris(shared_ptr<odb::database> db) {
	try {
		odb::transaction t(db->begin());
		// La operació query es fa servir per consultar (SELECT en SQL)
		odb::result<usuari> usuaris = db->query<usuari>();
		for (auto it = usuaris.begin(); it != usuaris.end(); ++it) {
			cout << "Username: " << it->get_username()
				<< ", Nom: " << it->get_nomcomplet()
				<< ", Edat: " << it->get_edat() << endl;
		}
		t.commit();
	}
	catch (const odb::exception& e) {
		cout << "Error al llegir els usuaris: " << e.what() << endl;
	}
}
void llegir_usuari(shared_ptr<odb::database> db) {
	string user_id;
	cout << "Username de l'usuari a consultar: ";
	cin >> user_id;
	try {
		odb::transaction t(db->begin());
		shared_ptr<usuari> u = db->load<usuari>(user_id);
		cout << "Username: " << u->get_username();
		cout << ", Nom: " << u->get_nomcomplet();
		cout << ", Edat: " << u->get_edat() << endl;
	}
	// Si l'usuari no existeix, es llença una excepció object_not_persistent
	catch (const odb::object_not_persistent&) {
		cout << "Usuari no trobat.\n";
	}
	catch (const odb::exception& e) {
		cout << "Error al llegir l'usuari: " << e.what() << endl;
	}
}
void actualitzar_usuari(shared_ptr<odb::database> db) {
	string user;
	cout << "Username de l'usuari a modificar: ";
	cin >> user;
	try {
		odb::transaction t(db->begin());
		shared_ptr<usuari> u = db->load<usuari>(user);
		string nou_nom;
		int nova_edat;
		cout << "Nou nom complet: ";
		cin.ignore();
		getline(cin, nou_nom);
		cout << "Nova edat: ";
		cin >> nova_edat;
		u->set_nomcomplet(nou_nom);
		u->set_edat(nova_edat);
		// La operació update es fa servir per modificar (UPDATE en SQL)
		db->update(u);
		t.commit();
		cout << "Usuari actualitzat.\n";
	}
	// Si l'usuari no existeix, es llença una excepció object_not_persistent
	catch (const odb::object_not_persistent&) {
		cout << "Usuari no trobat.\n";
	}
	catch (const odb::exception& e) {
		cout << "Error al actualitzar l'usuari: " << e.what() << endl;
	}
}
void esborrar_usuari(shared_ptr<odb::database> db) {
	string user;
	cout << "Username de l'usuari a esborrar: ";
	cin >> user;
	try {
		odb::transaction t(db->begin());
		// La operació erase es fa servir per esborrar (DELETE en SQL)
		db->erase<usuari>(user);
		cout << "Usuari esborrat.\n";
		t.commit();
	}
	catch (const odb::object_not_persistent&) {
		cout << "Usuari no trobat.\n";
	}
	catch (const odb::exception& e) {
		cout << "Error al esborrar l'usuari: " << e.what() << endl;
	}
}
void menu_usuari(shared_ptr<odb::database> db) {
	int opcio;
	do {
		cout << "\n--- MENU CRUD USUARI ---\n";
		cout << "1. Crear usuari\n";
		cout << "2. Llistar tots els usuaris\n";
		cout << "3. Consultar usuari\n";
		cout << "4. Actualitzar usuari\n";
		cout << "5. Esborrar usuari\n";
		cout << "0. Sortir\n";
		cout << "Opcio: ";
		cin >> opcio;
		switch (opcio) {
		case 1: crear_usuari(db); break;
		case 2: llegir_usuaris(db); break;
		case 3: llegir_usuari(db); break;
		case 4: actualitzar_usuari(db); break;
		case 5: esborrar_usuari(db); break;
		case 0: cout << "Adeu!\n"; break;
		default: cout << "Opcio no vàlida.\n"; break;
		}
	} while (opcio != 0);
}
int main() {
	// Connexió a la base de dades MySQL
	auto db = make_shared<odb::mysql::database>(
		"user", // usuari MySQL
		"password", // contrasenya MySQL
		"nomDB", // nom de la base de dades
		"host" // host
	);
	int opcio;
	do {
		cout << "\n--- MENU ---\n";
		cout << "1. Menu usuari\n";
		cout << "2. Menu perfil (no implementat encara)\n";
		cout << "3. Menu vehicles (no implementat encara)\n";
		cout << "4. Menu estudiants i assignatures (no implementat encara)\n";
		cout << "0. Sortir\n";
		cout << "Opcio: ";
		cin >> opcio;
		switch (opcio) {
		case 1: menu_usuari(db); break;
		case 2: /*menu_perfils(db);*/ break;
		case 3: /*menu_vehicles(db);*/ break;
		case 4: /*menu_estudiants_assignatures(db);*/ break;
		case 0: cout << "Adeu!\n"; break;
		default: cout << "Opcio no vàlida.\n"; break;
		}
	} while (opcio != 0);
	return 0;
}
