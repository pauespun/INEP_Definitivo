#include "CapaDePresentacio.hxx"
#include <iostream>
#include <string>
#include <limits> // Necessari per numeric_limits

using namespace std;

void CapaDePresentacio::crear_usuari()
{
    string sobrenom, nom, correu, contra;
    int edat;

    cout << "--- REGISTRE D'USUARI ---\n";
    cout << "Sobrenom (ID): ";
    cin >> sobrenom;

    cout << "Nom complet: ";
    cin.ignore();
    getline(cin, nom);

    cout << "Correu electronic: ";
    cin >> correu;

    cout << "Contrasenya: ";
    cin >> contra;

    cout << "Edat: ";
    cin >> edat;

    CapaDeDomini& domini = CapaDeDomini::getInstance();
    try {
        // Cridem al mètode actualitzat del domini
        domini.registrarUsuari(sobrenom, nom, correu, contra, edat);
        cout << "Usuari registrat correctament!\n";
    }
    catch (const exception& e) {
        cout << "[ERROR] " << e.what() << endl;
    }
}

void CapaDePresentacio::esborrar_usuari()
{
    string sobrenom;
    cout << "Sobrenom de l'usuari a esborrar: ";
    cin >> sobrenom;

    CapaDeDomini& domini = CapaDeDomini::getInstance();
    try {
        domini.esborrarUsuari(sobrenom);
        cout << "Usuari esborrat correctament.\n";
    }
    catch (const exception& e) {
        cout << "[ERROR] " << e.what() << endl;
    }
}

void CapaDePresentacio::actualitzar_usuari() {
    string sobrenom;
    cout << "Sobrenom de l'usuari a modificar: ";
    cin >> sobrenom;

    CapaDeDomini& domini = CapaDeDomini::getInstance();
    try {
        // Recuperem dades actuals
        DTOUsuari dto = domini.consultarUsuari(sobrenom);

        cout << "--- Dades actuals ---\n";
        cout << "Nom: " << dto.get_nom() << endl;
        cout << "Correu: " << dto.get_correuElectronic() << endl;
        cout << "Edat: " << dto.get_edat() << endl;

        // Netejem buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string nou_nom, nou_correu;
        int nova_edat = -1;

        cout << "\nNou nom (enter per mantenir): ";
        getline(cin, nou_nom);

        cout << "Nou correu (enter per mantenir): ";
        getline(cin, nou_correu);

        cout << "Nova edat (-1 per mantenir): ";
        string entrada_edat;
        getline(cin, entrada_edat);
        if (!entrada_edat.empty()) {
            try {
                nova_edat = stoi(entrada_edat);
            }
            catch (...) {}
        }

        // Cridem a modificar amb els nous paràmetres
        domini.modificarUsuari(sobrenom, nou_nom, nou_correu, nova_edat);
        cout << "Usuari actualitzat correctament.\n";
    }
    catch (const exception& e) {
        cout << "[ERROR] " << e.what() << endl;
    }
}

void CapaDePresentacio::llegir_usuari()
{
    string sobrenom;
    cout << "Sobrenom de l'usuari a consultar: ";
    cin >> sobrenom;

    CapaDeDomini& domini = CapaDeDomini::getInstance();
    try {
        DTOUsuari dto = domini.consultarUsuari(sobrenom);
        cout << "\n--- DETALL USUARI ---\n";
        cout << "Sobrenom: " << dto.get_sobrenom() << endl;
        cout << "Nom: " << dto.get_nom() << endl;
        cout << "Correu: " << dto.get_correuElectronic() << endl;
        cout << "Edat: " << dto.get_edat() << endl;
    }
    catch (const exception& e) {
        cout << "[ERROR] " << e.what() << endl;
    }
}

void CapaDePresentacio::llegir_usuaris() {
    cout << "[AVIS] Funcionalitat de llistar tots els usuaris pendent d'implementar al DAO.\n";
}