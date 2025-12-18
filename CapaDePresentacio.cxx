#include "CapaDePresentacio.hxx"
#include "CtrlIniciSessio.hxx"
#include "CtrlRegistraUsuari.hxx"
#include "CtrlTancaSessio.hxx"
#include "CtrlConsultaUsuari.hxx"
#include "PlanGo.hxx" 
#include <iostream>
// No hace falta incluir DAOUsuari.hxx aquí, la presentación habla con los Controladores.

using namespace std;

// Singleton
CapaDePresentacio& CapaDePresentacio::getInstance() {
    static CapaDePresentacio instance;
    return instance;
}

CapaDePresentacio::CapaDePresentacio() {}

// =========================================================
// 1. INICIAR SESSIÓ (Implementación del caso de uso 3.1.1)
// =========================================================
bool CapaDePresentacio::iniciarSessio() {
    string sobrenom, contrasenya;

    cout << "** Inici sessio **" << endl;
    cout << "Sobrenom: ";
    cin >> sobrenom;
    cout << "Contrasenya: ";
    cin >> contrasenya;

    // Creamos el controlador
    CtrlIniciSessio ctrl;

    try {
        // Llamamos a la lógica
        ctrl.iniciSessio(sobrenom, contrasenya);

        // Si no ha saltado error, es que ha ido bien [cite: 128]
        cout << "Sessio iniciada correctament!" << endl;

        return true; // Retorna true para cambiar de menú en main.cpp
    }
    catch (UsuariNoExisteix) {
        // Capturamos el struct vacío
        cout << "Hi ha hagut un error amb el sobrenom o la contrasenya" << endl; // [cite: 159]
    }
    catch (ErrorContrasenya) {
        cout << "Hi ha hagut un error amb el sobrenom o la contrasenya" << endl; // [cite: 159]
    }
    catch (std::exception& e) {
        cout << "Error inesperat: " << e.what() << endl;
    }

    return false; // Login fallido
}

// =========================================================
// 2. REGISTRAR USUARI (Implementación del caso de uso 3.1.3)
// =========================================================
void CapaDePresentacio::registrarUsuari() {
    string nom, sobrenom, contrasenya, correu;
    int edat;

    cout << "** Registre usuari **" << endl;

    // Limpiamos el buffer por si acaso venimos de un cin >> int
    cin.ignore();

    cout << "Nom complet: ";
    getline(cin, nom); // getline permite espacios

    cout << "Sobrenom: ";
    cin >> sobrenom;

    cout << "Contrasenya: ";
    cin >> contrasenya;

    cout << "Correu electronic: ";
    cin >> correu;

    cout << "Edat: ";
    cin >> edat;

    // Creamos controlador
    CtrlRegistraUsuari ctrl;

    try {
        ctrl.registrarUsuari(nom, sobrenom, contrasenya, correu, edat);
        cout << "Usuari registrat amb exit!" << endl; // [cite: 192]
    }
    catch (SobrenomExisteix) {
        cout << "Ja existeix un usuari amb aquest sobrenom" << endl; // [cite: 229]
    }
    catch (CorreuExisteix) {
        cout << "Ja existeix un usuari amb aquest correu electronic" << endl; // [cite: 231]
    }
    catch (MenorEdat) {
        cout << "No es pot registar un menor" << endl; // [cite: 232]
    }
    catch (std::exception& e) {
        cout << "Error tècnic: " << e.what() << endl;
    }
}

// =========================================================
// 3. TANCAR SESSIÓ (Implementación del caso de uso 3.1.2)
// =========================================================

void CapaDePresentacio::tancarSessio() {
    char opcio;

    // Escenari principal: El sistema pregunta
    cout << "Vols tancar la sessio? (S/N): ";
    cin >> opcio;

    if (opcio == 'S' || opcio == 's') {
        // CORRECCIÓN: Instanciamos el controlador DIRECTAMENTE (sin CapaDeDomini)
        CtrlTancaSessio ctrl;
        ctrl.tancaSessio();

        cout << "Sessio tancada correctament!" << endl;
    }
    // Escenari alternatiu: 'N', no fem res.
}

// Funciones pendientes (Stubs) para que compile el menú
void CapaDePresentacio::consultarUsuari() {
    std::cout << "** Consulta usuari **" << std::endl;

    try {
        CtrlConsultaUsuari ctrl;
        DTOUsuari info = ctrl.consultaUsuari();

        std::cout << "Nom: " << info.get_nom() << std::endl;
        std::cout << "Sobrenom: " << info.get_sobrenom() << std::endl;
        std::cout << "Correu electronic: " << info.get_correuElectronic() << std::endl;
        std::cout << "Edat: " << info.get_edat() << std::endl;
        std::cout << "Total reserves: " << info.get_totalReserves() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nPrem Intro per continuar...";
    std::cin.ignore();
    std::cin.get();
}
void CapaDePresentacio::modificarUsuari() { cout << "En construccio...\n"; }
bool CapaDePresentacio::esborrarUsuari() { cout << "En construccio...\n"; return false; }