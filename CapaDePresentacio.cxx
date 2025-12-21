#include "CapaDePresentacio.hxx"
#include "CtrlIniciSessio.hxx"
#include "CtrlRegistraUsuari.hxx"
#include "CtrlTancaSessio.hxx"
#include "CtrlConsultaUsuari.hxx"
#include "CtrlModificaUsuari.hxx"
#include "CtrlEsborrarUsuari.hxx"
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
		// Guardamos el sobrenom localmente
		usuariLoguejat = sobrenom;

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
void CapaDePresentacio::modificarUsuari() {
    using namespace std;
    cout << "** Modificar usuari **" << endl;

    CtrlModificaUsuari ctrl;

    // 1. MOSTRAR INFORMACIÓN ACTUAL (Escenario principal)
    try {
        // Llamamos a consultaUsuari del propio controlador de modificación
        DTOUsuari infoActual = ctrl.consultaUsuari();

        cout << "--- Dades actuals ---" << endl;
        cout << "Nom: " << infoActual.get_nom() << endl;
        cout << "Correu: " << infoActual.get_correuElectronic() << endl;
        cout << "Edat: " << infoActual.get_edat() << endl;
        cout << "---------------------" << endl;
    }
    catch (std::exception& e) {
        cout << "Error al recuperar dades: " << e.what() << endl;
        return; // Si no podemos leer, salimos
    }

    // 2. PEDIR DATOS NUEVOS
    cout << "(Deixa en blanc per mantenir el valor actual)" << endl;

    string nom, correu, edatStr;
    int edat = -1;

    cin.ignore(); // Limpiar buffer

    cout << "Nom complet: ";
    getline(cin, nom);

    cout << "Correu electronic: ";
    getline(cin, correu);

    cout << "Edat: ";
    getline(cin, edatStr);

    if (!edatStr.empty()) {
        try {
            edat = stoi(edatStr);
        }
        catch (...) {
            cout << "Format incorrecte. No es modificara l'edat." << endl;
            edat = -1;
        }
    }

    // 3. MODIFICAR Y MOSTRAR RESULTADO CONFIRMADO
    try {
        // El controlador nos devuelve la info leída directamente de la BD post-cambio
        DTOUsuari infoModificada = ctrl.modificaUsuari(nom, correu, edat);

        cout << "Usuari modificat correctament!" << endl;
        cout << "--- Dades actualitzades (Base de Dades) ---" << endl;
        cout << "Nom: " << infoModificada.get_nom() << endl;
        cout << "Correu: " << infoModificada.get_correuElectronic() << endl;
        cout << "Edat: " << infoModificada.get_edat() << endl;
    }
    catch (CorreuExisteix) {
        cout << "Error: El correu electronic ja existeix." << endl;
    }
    catch (MenorEdat) {
        cout << "Error: No es poden registrar usuaris menors." << endl;
    }
    catch (std::exception& e) {
        cout << "Error tècnic: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.get();
}

bool CapaDePresentacio::esborrarUsuari() {
    using namespace std;
    string contrasenya;
    char confirmacio;

    cout << "** Esborrar usuari **" << endl;

    // 1. Pedir contraseña
    cout << "Introdueix la teva contrasenya per confirmar: ";
    cin >> contrasenya;

    // 2. Pedir confirmación explícita
    cout << "Estas segur que vols donar-te de baixa? (S/N): ";
    cin >> confirmacio;

    if (confirmacio == 'S' || confirmacio == 's') {
        try {
            CtrlEsborrarUsuari ctrl;

            // 3. Llamar al controlador con la contraseña
            ctrl.esborrarUsuari(contrasenya);

            // Si llegamos aquí, se ha borrado bien
            // Limpiamos variable local
			usuariLoguejat = "";
            cout << "Usuari esborrat correctament. Fins aviat!" << endl;

            cout << "\nPrem Intro per continuar...";
            cin.ignore(); cin.get();

            return true; // Indica al Main que debe salir al menú de inicio
        }
        catch (ErrorContrasenya) {
            // Escenario alternativo: Contraseña incorrecta
            cout << "Error: La contrasenya no es correcta. L'usuari no s'ha esborrat." << endl;
        }
        catch (std::exception& e) {
            cout << "Error tècnic: " << e.what() << endl;
        }
    }
    else {
        // Escenario alternativo: Usuario no confirma
        cout << "Operacio cancel.lada." << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore(); cin.get();

    return false; // No se ha borrado, nos quedamos en el menú principal
}