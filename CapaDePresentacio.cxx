#include "CapaDePresentacio.hxx"
#include "CtrlIniciSessio.hxx"
#include "CtrlRegistraUsuari.hxx"
#include "CtrlTancaSessio.hxx"
#include "CtrlConsultaUsuari.hxx"
#include "CtrlModificaUsuari.hxx"
#include "CtrlEsborrarUsuari.hxx"
#include "CtrlReservaEscapada.hxx"
#include "CtrlReservaActivitat.hxx"
#include "CtrlConsultaExperiencies.hxx"

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



void CapaDePresentacio::reservarEscapada() {
    using namespace std;
    string nomEscapada;
    char confirmacio;

    cout << "** Reservar escapada **" << endl;

    // Limpiamos buffer si venimos de un menú numérico
    // cin.ignore(); // Descomenta si el menú anterior usaba cin >> int

    // 1. Pedir datos
    cout << "Nom: ";
    // Usamos getline por si el nombre tiene espacios (Ej: "Escapada Paris")
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nomEscapada);

    CtrlReservaEscapada ctrl;

    try {
        // 2. Llamada al Controlador: CONSULTA
        DTOExperiencia info = ctrl.consulta_escapada(nomEscapada);

        // 3. Mostrar información
        cout << "Descripcio: " << info.get_descripcio() << endl;
        cout << "Ciutat: " << info.get_ciutat() << endl;
        cout << "Places: " << info.get_maxim_places() << endl;
        cout << "Hotel: " << info.get_hotel() << endl;
        cout << "Nits: " << info.get_num_nits() << endl;
        cout << "Preu: " << info.get_preu() << endl;

        // 4. Confirmación
        cout << "Vols continuar amb la reserva? (S/N): ";
        cin >> confirmacio;

        if (confirmacio == 'S' || confirmacio == 's') {
            // 5. Llamada al Controlador: RESERVA
            float preuPagat = ctrl.reserva_escapada();

            cout << "Reserva enregistrada correctament." << endl;
            cout << "Preu aplicat a la reserva: " << preuPagat << endl;
        }
        else {
            cout << "Operacio cancel.lada." << endl;
        }
    }
    catch (EscapadaNoExisteix) {
        cout << "L'escapada no existeix." << endl;
    }
    catch (std::exception& e) {
        cout << "Error inesperat: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}

void CapaDePresentacio::reservarActivitat() {
    using namespace std;
    string nomActivitat;
    int numPersones;
    char confirmacio;

    cout << "** Reservar activitat **" << endl;

    cout << "Introdueix el nom de l'activitat a reservar: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nomActivitat);

    CtrlReservaActivitat ctrl;

    try {
        DTOExperiencia info = ctrl.consulta_activitat(nomActivitat);

        cout << "Nom: " << info.get_nom() << endl;
        cout << "Descripcio: " << info.get_descripcio() << endl;
        cout << "Ciutat: " << info.get_ciutat() << endl;
        cout << "Places: " << info.get_maxim_places() << endl;
        cout << "Preu: " << info.get_preu() << endl;
        cout << "Durada (minuts): " << info.get_durada() << endl;

        float preuTotal = 0.0f;

        // ✅ Pedir numPersones hasta que ctrl.preu_total lo acepte
        while (true) {
            cout << "Introdueix el nombre de persones que volen realitzar l'activitat: ";
            cin >> numPersones;

            if (numPersones < 1) {
                cout << "Error: el nombre de persones ha de ser com a minim 1." << endl;
                continue;
            }

            try {
                preuTotal = ctrl.preu_total(numPersones); // ✅ aquí valida plazas reales
                break; // ok
            }
            catch (SuperaMaxim) {
                cout << "Error: No hi ha places suficients disponibles." << endl;
                cout << "Vols introduir un altre nombre? (S/N): ";
                cin >> confirmacio;

                if (confirmacio == 'N' || confirmacio == 'n') {
                    cout << "Operacio cancel·lada." << endl;
                    cout << "\nPrem Intro per continuar...";
                    cin.ignore(); cin.get();
                    return;
                }
            }
        }

        cout << "Preu total de la reserva: " << preuTotal << endl;

        cout << "Vols continuar amb la reserva? (S/N): ";
        cin >> confirmacio;

        if (confirmacio == 'S' || confirmacio == 's') {
            float preuPagat = ctrl.reserva_activitat(numPersones);
            cout << "Reserva enregistrada correctament." << endl;
            cout << "Preu aplicat a la reserva: " << preuPagat << endl;
        }
        else {
            cout << "Operacio cancel·lada." << endl;
        }
    }
    catch (ActivitatNoExisteix) {
        cout << "L'activitat no existeix." << endl;
    }
    catch (std::exception& e) {
        cout << "Error inesperat: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}


// =========================================================
// 3. CONSULTAR EXPERIENCIES (Implementación del caso de uso 3.3.1)
// =========================================================
void CapaDePresentacio::consultarExperiencies() {
    using namespace std;

    string ciutat;
    int numPersones;

    cout << "** Consultar experiències **" << endl;

    cout << "Introdueix la ciutat: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, ciutat);

    cout << "Introdueix el nombre de persones: ";
    cin >> numPersones;

    try {
        CtrlConsultaExperiencies ctrl;

        auto escapades = ctrl.consulta_escapades(ciutat, numPersones);
        auto activitats = ctrl.consulta_activitats(ciutat, numPersones);

        cout << "\n--- Escapades ---" << endl;
        if (escapades.empty()) {
            cout << "No hi ha escapades disponibles." << endl;
        }
        for (const auto& e : escapades) {
            cout << "Nom: " << e.get_nom() << endl;
            cout << "Descripcio: " << e.get_descripcio() << endl;
            cout << "Ciutat: " << e.get_ciutat() << endl;
            cout << "Places: " << e.get_maxim_places() << endl;
            cout << "Preu: " << e.get_preu() << endl;
            cout << "Hotel: " << e.get_hotel() << endl;
            cout << "Nits: " << e.get_num_nits() << endl;
            cout << "-----------------------------" << endl;
        }

        cout << "\n--- Activitats ---" << endl;
        if (activitats.empty()) {
            cout << "No hi ha activitats disponibles." << endl;
        }
        for (const auto& a : activitats) {
            cout << "Nom: " << a.get_nom() << endl;
            cout << "Descripcio: " << a.get_descripcio() << endl;
            cout << "Ciutat: " << a.get_ciutat() << endl;
            cout << "Places: " << a.get_maxim_places() << endl;
            cout << "Preu: " << a.get_preu() << endl;
            cout << "Durada: " << a.get_durada() << endl;
            cout << "-----------------------------" << endl;
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPrem Intro per continuar...";
    cin.ignore();
    cin.get();
}
